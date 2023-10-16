//
// Created by xiaoxi on 2023/10/16.
//
#include <common/common.h>
#include <stdio.h>
#include <malloc.h>

void add_object_node(ObjectList* oList, ObjectNode* node){
    if(oList->head == NULL && oList->tail == NULL){
        oList->head = node;
        oList->tail = node;
    }
    else{
        node->next = oList->tail->next;
        oList->tail->next = node;
        node->prev = oList->tail;
        oList->tail = node;
    }
}

void delete_object_node(ObjectList* oList,ObjectNode* node){
    if(oList->head == oList->tail && oList->head ==node){
        oList->head = oList->tail = NULL;
    }
    else if(oList->head == node){
        oList->head = node->next;
        node->next->prev = NULL;
    }
    else if(oList->tail == node){
        oList->tail = node->prev;
        oList->tail->next = NULL;
    }
    else{
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    free(node);
}
void free_object_node(ObjectNode* node){
    free(node->name);
    free_value_node(node->value);
}
void free_objectList(ObjectList* oList){
    ObjectNode* next = oList->head,*tmp;
    while(next){
        tmp = next;
        next = next->next;
        free(tmp);
    }
    if(oList!=NULL)
        free(oList);
}


void add_value_node(ArrayList* aList,ValueNode* node){
    if(aList->head == NULL && aList->tail == NULL){
        aList->head = node;
        aList->tail = node;
    }
    else{
        node->next = aList->tail->next;
        aList->tail->next = node;
        node->prev = aList->tail;
        aList->tail = node;
    }
}

void free_value_node(ValueNode* node){
    if(node == NULL)
        return;
    switch (node->type) {
        case t_string:
            free(node->value.str);
            break;
        case t_object:
            free_objectList(node->value.object);
            break;
        case t_array:
            free_arrayList(node->value.array);
            break;
    }
}

void free_arrayList(ArrayList * aList){
    ValueNode *next = aList->head,*tmp;
    while(next){
        tmp = next;
        next = next->next;
        free_value_node(tmp);
    }
}