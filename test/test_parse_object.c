#include <stdio.h>
#include <stdlib.h>
#include "common/common.h"
#include "parse/parse.h"

//
// Created by xiaoxi on 2023/10/16.
//
int main(){
    char test[][BUFFER_SIZE]={"{\"test_number\":34e3,\"test_string\":\"kdjslid\\\\\"}","{\"test_array\":[38749e-4,\"fas\"],\"test_object\":{\"ssa\":324}}"};
    init(stdin);
    ObjectList* json = parse_object();
    ObjectNode* next = json->head,*tmp;
    while(next){
        next = next->next;
    }

    free_objectList(json);


}