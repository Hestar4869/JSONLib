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
    struct ObjectList* object;
    struct ArrayList* array;
    bool tf;
    void* ptr;
} Value;

/**
 * 表示json中的值以及具体类型
 */
typedef struct ValueNode{
    ValueType type;
    Value value;
    // 当type==t_array时，next指向下一个值节点，其他时候不使用该属性
    struct ValueNode* next;
    struct ValueNode* prev;
}ValueNode;

/**
 * 表示json对象
 */
typedef struct ObjectNode{
    char* name;
    struct ValueNode* value;
    struct ObjectNode* next;
    struct ObjectNode* prev;
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

// 基本数据结构的增删查改
ObjectNode* create_object_node(char* name,ValueNode* value);
ObjectList* create_object_list();
void add_object_node(ObjectList* oList, ObjectNode* node);
void delete_object_node(ObjectList* oList,ObjectNode* node);
void free_objectList(ObjectList* oList);
void free_object_node(ObjectNode* node);
ValueNode* find_value_by_name(ObjectList* aList,char* name);

ValueNode* create_value_node(ValueType type,Value value);
ValueNode* create_number(double num);
ValueNode* create_string(char* str);
ValueNode* create_bool(bool tf);
ValueNode* create_null();
ValueNode* create_array(ArrayList* aList);
ArrayList* create_array_list();
void add_value_node(ArrayList* aList,ValueNode* node);
void delete_value_node(ArrayList* aList,ValueNode* node);
void free_arrayList(ArrayList * aList);
void free_value_node(ValueNode* node);

#endif //JSONLIB_COMMON_H
