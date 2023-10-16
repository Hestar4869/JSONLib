#include <stdio.h>
#include "common/common.h"
#include "parse/parse.h"

//
// Created by xiaoxi on 2023/10/16.
//
int main(){
    char test[][BUFFER_SIZE]={"[45235,4e3,5e-2]","[\"hflas\",8473.54,\"fasf\\t643\"]"};
    for (int i = 0; i < 2; ++i) {
        FILE* file = fopen("test_parse_arraytext.txt","w");
        fprintf(file,"%s",test[i]);
        fclose(file);
        file = fopen("test_parse_arraytext.txt","r");
        printf("当前检测test%d: %s\n",i,test[i]);
        init(file);
        ArrayList* aList = parse_array();
        ValueNode* next = aList->head;
        while(next){
            switch (next->type) {
                case t_number:
                    printf("%f\n",next->value.number);
                    break;
                case t_string:
                    printf("%s\n",next->value.str);
            }
            next = next->next;
        }
        free_arrayList(aList);
        fclose(file);
    }
}