//
// Created by xiaoxi on 2023/10/17.
//

#include <common/common.h>
#include <serialize/serialize.h>
int main(){
    ObjectList* json = create_object_list();
    ValueNode* val1 = create_bool(true);
    ValueNode* val2 = create_string("this is a string");
    ValueNode* val3 = create_number(2314.234);
    ValueNode* val4 = create_null();
    ArrayList* alist = create_array_list();
    add_value_node(alist, val1);
    add_value_node(alist, val2);
    ValueNode* val5 = create_array(alist);

    ObjectNode* ob1= create_object_node("bool",val1);
    ObjectNode* ob2 = create_object_node("string",val2);
    ObjectNode* ob3 = create_object_node("number",val3);
    ObjectNode* ob4 = create_object_node("null",val4);
    ObjectNode* ob5 = create_object_node("array", val5);

    add_object_node(json,ob1);
    add_object_node(json,ob2);
    add_object_node(json,ob3);
    add_object_node(json,ob4);
    add_object_node(json,ob5);

    serialize_init(stdout);
    serialize_object(json);

}