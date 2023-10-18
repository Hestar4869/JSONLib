//
// Created by xiaoxi on 2023/10/16.
//
#include <common/common.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

ObjectNode* create_object_node(char* name,ValueNode* value){
    char* _name = calloc(strlen(name)+1, sizeof(char));
    strcpy(_name,name);
    ObjectNode* onode = calloc(1, sizeof(ObjectNode));
    onode->name = _name;
    onode->value = value;
    return onode;
}

ObjectList* create_object_list(){
    ObjectList* olist = calloc(1, sizeof(ObjectList));
    return olist;
}

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
    free_object_node(node);
}

void free_object_node(ObjectNode* node){
    free(node->name);
    free_value_node(node->value);
    free(node);
}

void free_objectList(ObjectList* oList){
    ObjectNode* next = oList->head,*tmp;
    while(next){
        tmp = next;
        next = next->next;
        free_object_node(tmp);
    }

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
        default:
            // 对于t_number , t_null , t_bool不做任何处理
            break;
    }
    free(node);
}

void free_arrayList(ArrayList * aList){
    ValueNode *next = aList->head,*tmp;
    while(next){
        tmp = next;
        next = next->next;
        free_value_node(tmp);
    }
    free(aList);
}

ArrayList* create_array_list(){
    ArrayList* alist = calloc(1, sizeof(ArrayList));
    return alist;
}

ValueNode* create_value_node(ValueType type,Value value){
    ValueNode *vnode = NULL;
    switch (type) {
        case t_bool:
            vnode = create_bool(value.tf);
            break;
        case t_null:
            vnode = create_null();
            break;
        case t_object:
            vnode = calloc(1, sizeof(ValueNode));
            vnode->type = t_object;
            vnode->value = value;
            break;
        case t_array:
            vnode = calloc(1, sizeof(ValueNode));
            vnode->type = t_array;
            vnode->value = value;
            break;
        case t_string:
            vnode = create_string(value.str);
            break;
        case t_number:
            vnode = create_number(value.number);
            break;
    }
    return vnode;
}

ValueNode* create_number(double num){
    ValueNode* vnode = calloc(1, sizeof(ValueNode));
    vnode->type = t_number;
    vnode->value.number = num;
    return vnode;
}

ValueNode* create_string(char* str){
    ValueNode* vnode = calloc(1, sizeof(ValueNode));
    vnode->type = t_string;
    vnode->value.str = calloc(strlen(str)+1,sizeof(char ));
    strcpy(vnode->value.str,str);
    return vnode;
}

ValueNode* create_bool(bool tf){
    ValueNode* vnode = calloc(1, sizeof(ValueNode));
    vnode->type = t_bool;
    vnode->value.tf = tf;
    return vnode;
}

ValueNode* create_null(){
    ValueNode* vnode = calloc(1, sizeof(ValueNode));
    vnode->type = t_bool;
    vnode->value.ptr = NULL;
    return vnode;
}

ValueNode* create_array(ArrayList* aList){
    ValueNode* vnode = calloc(1, sizeof(ValueNode));
    vnode->type = t_array;
    vnode->value.array = aList;
    return vnode;
}

void delete_value_node(ArrayList* aList,ValueNode* node){
    if(aList->head == aList->tail && aList->head ==node){
        aList->head = aList->tail = NULL;
    }
    else if(aList->head == node){
        aList->head = node->next;
        node->next->prev = NULL;
    }
    else if(aList->tail == node){
        aList->tail = node->prev;
        aList->tail->next = NULL;
    }
    else{
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }
    free_value_node(node);
}

ValueNode* find_value_by_name(ObjectList* aList,char* name){
    ObjectNode* node = aList->head;
    while(node){
        if(!strcmp(name,node->name)){
            return node->value;
        }
    }
    // 未找到对应的键值对
    return NULL;
}