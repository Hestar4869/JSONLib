//
// Created by xiaoxi on 2023/10/12.
//

#include <stdio.h>
#include<ctype.h>
#include <malloc.h>
#include "parse.h"
#include <common/error.h>
#include <string.h>

ObjectList* parse_object(){
    // 处理空白字符
    char ch = deal_whitespace();

    // 读入字符串name
    char* name=NULL;
    name = parse_string();
    if(name == NULL){
        sprintf(stderr,"%s:name部分字符串解析错误\n",ERROR_PARSE_OBJECT);
        return NULL;
    }

    // 处理冒号
    ch = deal_whitespace();
    ch = getchar();
    if(ch != ':'){
        sprintf(stderr,"%s:检测到字符%c,缺乏冒号:\n",ERROR_PARSE_OBJECT,ch);
        free(name);
        return NULL;
    }

    // 处理值类型
    ch = deal_whitespace();
    ValueNode* value;
    value = parse_value();
}

char* parse_string(){
    char ch = getchar();
    // 检测上引号
    if(ch!='\"'){
        sprintf(stderr,"%s:缺乏上引号\"\n",ERROR_PARSE_STRING);
        return NULL;
    }

    char* str = malloc(BUFFER_SIZE*sizeof(char));
    memset(str,'\0',BUFFER_SIZE);
    int index=0;

    while( (ch = getchar()) && index<BUFFER_SIZE){
        if(ch == '\\'){
            ch = getchar();
            if(!isescape(ch)){
                sprintf(stderr,"%s: 不存在转义字符\\%c\n",ERROR_PARSE_STRING,ch);
                free(str);
                return NULL;
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
        sprintf(stderr,"%s: %s缺乏下引号\"\n",ERROR_PARSE_STRING,str);
        free(str);
        return NULL;
    }

    return str;
}

ValueNode* parse_value(){
    char ch = getchar();

}

char deal_whitespace(){
    char ch;
    while(isspace(ch=peek_char())){
        ch = getchar();
    }
    return ch;
}

char peek_char(){
    char ch = getchar();
    // 将取出的字符放回输入缓冲区
    ungetc(ch,stdin);
    return ch;
}

bool isescape(char ch){
    const char escape[]={'\"','\\','\/','\b',
                         '\f','\n','\r','\t'};

    for(int i=0;i<8;i++){
        if(ch == escape[i])
            return true;
    }
    return false;
}