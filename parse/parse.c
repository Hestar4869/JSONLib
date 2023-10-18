//
// Created by xiaoxi on 2023/10/12.
//

#include <stdio.h>
#include<ctype.h>
#include "parse.h"
#include <common/error.h>
#include <string.h>
#include <stdlib.h>
static FILE* stream;

static bool isescape(char ch);
bool parse_init(FILE* origin){
    stream = origin;
    return true;
}

ObjectList* parse_object(){
    if(getc(stream) != '{')
        return NULL;

    ObjectList* oList = calloc(1,sizeof(ObjectList));
    while(1)
    {
        // 处理空白字符
        char ch = deal_whitespace();

        // 读入字符串name
        char *name = NULL;
        name = parse_string();
        if (name == NULL) {
            fprintf(stderr, "%s:name部分字符串解析错误\n", ERROR_PARSE_OBJECT);
            free_objectList(oList);
            return NULL;
        }

        // 处理冒号
        ch = deal_whitespace();
        ch = getc(stream);
        if (ch != ':') {
            fprintf(stderr, "%s:检测到字符%c,缺乏冒号:\n", ERROR_PARSE_OBJECT, ch);
            free_objectList(oList);
            return NULL;
        }

        // 处理值类型
        ch = deal_whitespace();
        ValueNode *value;
        value = parse_value();

        ObjectNode* oNode= calloc(1,sizeof (ObjectNode));
        oNode->name = name;
        oNode->value=value;

        //将该对象节点加入到对象集合中
        add_object_node(oList,oNode);

        // 处理分隔符或反大括号
        deal_whitespace();
        ch = getc(stream);
        if(ch == ',')
            continue;
        else if(ch == '}')
            break;
        else{
            fprintf(stderr,"%s:上一个对象解析完成后，未检测到','或'}'，而是'%c'",ERROR_PARSE_OBJECT,ch);
            // todo print error object

            free_objectList(oList);
            return NULL;
        }
    }
    return oList;
}

char* parse_string(){
    char ch = getc(stream);
    // 检测上引号
    if(ch!='\"'){
        fprintf(stderr,"%s:缺乏上引号\"\n",ERROR_PARSE_STRING);
        return NULL;
    }

    char* str = calloc(BUFFER_SIZE,sizeof(char));

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
    char* str = calloc(BUFFER_SIZE, sizeof(char));
    int index = 0;
    char ch = peek_char();
    if(ch == '-') {
        str[index++] = ch;
        getc(stream);
    }
    // 读入整数部分数字
    while(isdigit( ch = peek_char())){
        str[index++] = ch;
        ch = getc(stream);
    }

    // 解析fraction部分
    if(ch == '.') {
        str[index++] = ch;
        ch = getc(stream);
        //接着处理数字部分
        while(isdigit( ch = peek_char())){
            str[index++] = ch;
            ch = getc(stream);
        }
    }

    // 解析exponent部分出错
    if(ch=='e'||ch=='E'){
        str[index++] = ch;
        getc(stream);
        ch = peek_char();
        if(ch == '-' || ch == '+') {
            str[index++] = ch;
            ch = getc(stream);
        }
        //接着处理数字部分
        while(isdigit( ch = peek_char())){
            str[index++] = ch;
            ch = getc(stream);
        }
    }

    double ret = strtod(str,NULL);
    free(str);
    return ret;
}

ValueNode* parse_value(){
    char ch = peek_char();
    ValueNode* val = calloc(1,sizeof(ValueNode));
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
    else
        return NULL;

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
        case t_array: {
            val->value.array = parse_array();
            break;
        }
        case t_bool:
        case t_null: {
            char *str = parse_constant();
            if (!str) break;
            if(str[0] == 'f')
                val->value.tf = false;
            else if(str[0] == 't')
                val->value.tf = true;
            else if(str[0] == 'n')
                val->value.ptr = NULL;
            // 释放掉parse_constant()函数内申请的内存空间
            free(str);
        }

    }

    return val;

}
char* parse_constant(){
    char* constant = calloc(7, sizeof(char));
    char ch = peek_char();
    if(ch == 'n' || ch == 't'){
        fgets(constant,5,stream);
    }
    else if( ch == 'f')
        fgets(constant,6,stream);
    if((ch == 'n' && !strcmp(constant,"null")) || (ch=='t'&& !strcmp(constant,"true")) || (ch=='f'&& !strcmp(constant,"false"))){
        return constant;
    }
    else{
        fprintf(stderr,"%s:不存在常量%s\n",ERROR_PARSE_CONSTANT,constant);
        free(constant);
        return NULL;
    }

}
ArrayList* parse_array(){
    char ch = getc(stream);
    if(ch !='[')
        return NULL;

    ArrayList* aList = calloc(1,sizeof(ArrayList));
    memset(aList,0, sizeof(ArrayList));

    while(1){
        // 处理空白字符
        ch = deal_whitespace();

        //处理数组的值
        ValueNode *value = parse_value();

        //将值加入到数组中
        if(value!=NULL)
            add_value_node(aList,value);

        // 处理分隔符或反中括号
        deal_whitespace();
        ch = getc(stream);
        if(ch == ',')
            continue;
        else if(ch == ']')
            break;
        else{

            fprintf(stream,"%s:未检测到分隔符或反中括号，仅检测到'%c'",ERROR_PARSE_ARRAY,ch);
            free_arrayList(aList);
            free(aList);
            return NULL;
        }
    }
    return aList;
}
char deal_whitespace(){
    char ch;
    while(isspace(ch=peek_char())){
        getc(stream);
    }
    return ch;
}

char peek_char(){
    char ch = getc(stream);
    // 将取出的字符放回输入缓冲区
    ungetc(ch,stream);
    return ch;
}

static bool isescape(char ch){
    const char escape[]={'\"','\\','/','b',
                         'f','n','r','t'};

    for(int i=0;i<8;i++){
        if(ch == escape[i])
            return true;
    }
    return false;
}