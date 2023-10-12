//
// Created by xiaoxi on 2023/10/12.
//

#ifndef JSONLIB_COMMON_H
#define JSONLIB_COMMON_H
#include<stdbool.h>
#define BUFFER_SIZE 512

typedef enum ValueType{
    t_string,t_number,t_object,t_array,t_bool,t_null
} ValueType;

/**
 * 存储json中的值，值的类型可能为字符串，数组，数字，json对象，NULL，bool
 */
typedef union Value{
    char* str;
    double number;
    struct ObjectNode* object;
    struct ValueNode* array;
    bool tf;
    void* ptr;
} Value;

/**
 * 表示json中的值以及具体类型
 */
typedef struct ValueNode{
    ValueType type;
    Value value;
}ValueNode;

/**
 * 表示json对象
 */
typedef struct ObjectNode{
    char* name;
    struct ValueNode value;
    struct ObjectNode* next;
} ObjectNode;

/**
 * 用链表形式存储json对象集合
 */
typedef struct ObjectList{
    struct ObjectNode* head;
    struct ObjectNode* tail;
} ObjectList;

/**
 * 存储数组类型
 */
typedef struct ArrayList{
    struct ValueNode* head;
    struct ValueNode* tail;
} ArrayList;

void add_object_node(ObjectNode* oList, ObjectNode* node);
void delete_object_node(ObjectNode* node);

#endif //JSONLIB_COMMON_H
