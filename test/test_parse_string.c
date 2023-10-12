//
// Created by xiaoxi on 2023/10/12.
//
#include<stdio.h>
#include "parse/parse.h"

int main(){
    char test[][15]={"\"sda\\/\\\n\\\"","\"2'//as342hfkl\""};
    for(int i=0;i<2;i++){
        printf("当前检测test%d:%s\n");
        fprintf(stdin,"%s",test[i]);
        char *str;
        str = parse_string();
        printf("%s\n",str);
    }
}