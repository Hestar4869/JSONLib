//
// Created by xiaoxi on 2023/10/12.
//

#include <stdio.h>
#include<ctype.h>
#include <malloc.h>
#include "parse.h"
#include <common/error.h>
#include <string.h>
static FILE* stream;

bool init(FILE* origin){
    stream = origin;
    return true;
}

ObjectList* parse_object(){
    ObjectList* oList;
    while(1)
    {
        // 处理空白字符
        char ch = deal_whitespace();

        // 读入字符串name
        char *name = NULL;
        name = parse_string();
        if (name == NULL) {
            fprintf(stderr, "%s:name部分字符串解析错误\n", ERROR_PARSE_OBJECT);
            return NULL;
        }

        // 处理冒号
        ch = deal_whitespace();
        ch = getchar();
        if (ch != ':') {
            fprintf(stderr, "%s:检测到字符%c,缺乏冒号:\n", ERROR_PARSE_OBJECT, ch);
            free(name);
            return NULL;
        }

        // 处理值类型
        ch = deal_whitespace();
        ValueNode *value;
        value = parse_value();

        ObjectNode* oNode= malloc(sizeof (ObjectNode));
        oNode->value=value
    }

    //
}

char* parse_string(){
    char ch = getc(stream);
    // 检测上引号
    if(ch!='\"'){
        fprintf(stderr,"%s:缺乏上引号\"\n",ERROR_PARSE_STRING);
        return NULL;
    }

    char* str = malloc(BUFFER_SIZE*sizeof(char));
    memset(str,'\0',BUFFER_SIZE);
    int index=0;

    while( (ch = getc(stream)) && index<BUFFER_SIZE){
        if(ch == '\\'){
            ch = getc(stream);
            if(!isescape(ch)){
                fprintf(stderr,"%s: 不存在转义字符\\%c\n",ERROR_PARSE_STRING,ch);
                free(str);
                return NULL;
            }
            switch (ch) {
                case 'b':
                    ch = '\b';
                    break;
                case 'f':
                    ch = '\f';
                    break;
                case 'n':
                    ch = '\n';
                    break;
                case 'r':
                    ch = '\r';
                    break;
                case 't':
                    ch = '\t';
                default:
                    // 字符'\\' '\"' '/'等不变
                    ch = ch;
            }
        }
        else if(ch == '\"'){
            break;
        }
        // todo index长度检测，动态扩容
        str[index] = ch;
        index++;
    }

    if(ch != '\"'){
        fprintf(stderr,"%s: %s缺乏下引号\"\n",ERROR_PARSE_STRING,str);
        free(str);
        return NULL;
    }

    return str;
}

double parse_number() {
    // 一个number类型，应该包括三个部分 integer fraction exponent

    // 解析integer部分
    char* str = malloc(BUFFER_SIZE);
    memset(str,'\0',BUFFER_SIZE);
    int index = 0;
    char ch = peek_char();
    if(ch == '-') {
        str[index++] = ch;
        getc(stream);
    }
    // 读入整数部分数字
    while(isdigit( ch = peek_char())){
        str[index++] = ch;
        getc(stream);
    }

    // 解析fraction部分
    if(ch == '.') {
        str[index++] = ch;
        getc(stream);
        //接着处理数字部分
        while(isdigit( ch = peek_char())){
            str[index++] = ch;
            getc(stream);
        }
    }

    // 解析exponent部分出错
    if(ch=='e'||ch=='E'){
        str[index++] = ch;
        getc(stream);
        ch = peek_char();
        if(ch == '-' || ch == '+') {
            str[index++] = ch;
            getc(stream);
        }
        else{
            fprintf(stderr,"%s:解析exponent部分出错,未检测到e后面的加减号\n",ERRPR_PARSE_NUMBER);
            // todo 设置errno提醒出现异常
            return 0;
        }
        //接着处理数字部分
        while(isdigit( ch = peek_char())){
            str[index++] = ch;
            getc(stream);
        }
    }

    double ret = strtod(str,NULL);

    return ret;
}

ValueNode* parse_value(){
    char ch = peek_char();
    ValueNode* val = malloc(sizeof(ValueNode));
    if(ch == '\"')
        val->type = t_string;
    else if(ch == '-' || isdigit(ch))
        val->type = t_number;
    else if(ch == '{')
        val->type = t_object;
    else if(ch == '[')
        val->type = t_array;
    else if(ch == 't' || ch == 'f')
        val->type = t_bool;
    else if(ch == 'n')
        val->type = t_null;

    switch (val->type) {
        case t_string:
            val->value.str = parse_string();
            break;
        case t_number:
            val->value.number = parse_number();
            break;
        case t_object:
            val->value.object = parse_object();
            break;
        case t_array:
            val->value.array = parse_array();
            break;
        case t_bool:
        case t_null:
            val->value.ptr = NULL;
    }
    return val;

}
ValueNode* parse_array(){
    // todo
}
char deal_whitespace(){
    char ch;
    while(isspace(ch=peek_char())){
        ch = getc(stream);
    }
    return ch;
}

char peek_char(){
    char ch = getc(stream);
    // 将取出的字符放回输入缓冲区
    ungetc(ch,stdin);
    return ch;
}

bool isescape(char ch){
    const char escape[]={'\"','\\','/','b',
                         'f','n','r','t'};

    for(int i=0;i<8;i++){
        if(ch == escape[i])
            return true;
    }
    return false;
}