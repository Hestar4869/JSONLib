//
// Created by xiaoxi on 2023/10/12.
//
#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse/parse.h"

int main(){
    char test[][15]={"\"sda\\/\\n\\\"\"","\"2'//as342hfkl\""};

    for(int i=0;i<2;i++){
        FILE* file = fopen("test_parse_stringtext.txt","w");
        fprintf(file,"%s",test[i]);
        fclose(file);
        file = fopen("test_parse_stringtext.txt","r");
        printf("当前检测test%d: %s\n",i,test[i]);
        char *str;
        parse_init(file);
        str = parse_string();
        if(str == NULL)
            exit(-1);
        printf("%s\n",str);
        fclose(file);
    }
}