//
// Created by xiaoxi on 2023/10/16.
//

#include <stdlib.h>
#include <string.h>
#include "serialize.h"

static FILE* stream;
static bool isescape(char ch);
void serialize_init(FILE* origin){
    stream = origin;
}

void serialize_object(ObjectList* oList){
    ObjectNode* node = oList->head;
    putc('{',stream);


    while(node) {
        if(node != oList->head)
            putc(',',stream);

        fprintf(stream,"\"%s\"",node->name);
        putc(':',stream);

        switch (node->value->type) {
            case t_number:
                serialize_number(node->value->value.number);
                break;
            case t_string:
                serialize_string(node->value->value.str);
                break;
            case t_array:
                serialize_array(node->value->value.array);
                break;
            case t_object:
                serialize_object(node->value->value.object);
                break;
            case t_bool:
            case t_null:
                serialize_constant(node->value);
        }
        node = node->next;
    }
    putc('}',stream);

}
void serialize_number(double num){
    fprintf(stream,"%g",num);
}
void serialize_constant(ValueNode* node){
    if(node->type == t_bool && node->value.tf == true)
        fputs("true",stream);
    else if(node->type == t_bool && node->value.tf == false)
        fputs("false",stream);
    else
        fputs("null",stream);
}
void serialize_array(ArrayList* aList){
    ValueNode* node = aList->head;
    putc('[',stream);
    while(node) {
        if(node != aList->head)
            putc(',',stream);
        switch (node->type) {
            case t_number:
                serialize_number(node->value.number);
                break;
            case t_string:
                serialize_string(node->value.str);
                break;
            case t_array:
                serialize_array(node->value.array);
                break;
            case t_object:
                serialize_object(node->value.object);
                break;
            case t_bool:
            case t_null:
                serialize_constant(node);
        }
        node = node->next;
    }
    putc(']',stream);

}
void serialize_string(char* str){
    putc('\"',stream);
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        // 判断是否为转义字符
        if(isescape(str[i])){
            // 先输出转义符号
            putc('\\',stream);
            char ch;
            // 若是可打印字符，直接打印
            if(str[i] == '\"' || str[i] =='\\' || str[i]=='/')
                ch = str[i];
            // 不可打印字符，单独转换成对应转义字符
            switch (str[i]) {
                case '\b':
                    ch = 'b';
                    break;
                case '\f':
                    ch = 'f';
                    break;
                case '\n':
                    ch = 'n';
                    break;
                case '\r':
                    ch = 'r';
                    break;
                case '\t':
                    ch = 't';
                    break;
            }
            putc(ch,stream);
        }
        else
            putc(str[i],stream);
    }
    putc('\"',stream);
}

static bool isescape(char ch){
    const char escape[] = {   '\"', '\\', '/', '\b',
                            '\f', '\n', '\r','\t'};
    for(int i=0;i<8;i++){
        if(ch == escape[i])
            return true;
    }
    return false;
}