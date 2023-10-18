//
// Created by xiaoxi on 2023/10/17.
//
#include <parse/parse.h>
#include <serialize/serialize.h>
#include <common/common.h>
int main(){
    // 初始化解析数据流,这里暂定从标准输入流解析
    parse_init(stdin);

    // 解析json字符串
    ObjectList* olist = parse_object();

    // 初始化序列化数据流，这里暂定向标准输出流输出
    serialize_init(stdout);

    // 序列化内存对象并输出
    putchar('\n');
    serialize_object(olist);

    // 对json增加一个新字符串
    ValueNode* val1 = create_string("this is a new string");
    ObjectNode* ob1 = create_object_node("new_string",val1);
    add_object_node(olist,ob1);

    //再增加一个新数组类型
    ArrayList* alist = create_array_list();
    ValueNode* number1 = create_number(111.11);
    ValueNode* number2 = create_number(222.22);
    ValueNode* number3 = create_number(333);
    add_value_node(alist,number1);
    add_value_node(alist,number2);
    add_value_node(alist,number3);
    ValueNode* val2 = create_array(alist);
    ObjectNode* ob2 = create_object_node("new_array",val2);
    add_object_node(olist,ob2);

    putchar('\n');
    serialize_object(olist);

    // 查找nam为"min_position"的值
    ValueNode* tmp = find_value_by_name(olist,"min_position");
    printf("\nmin_position的值为%g\n",tmp->value.number);

    // 删除第一个元素以及ob1
    delete_object_node(olist,olist->head);
    delete_object_node(olist,ob1);

    serialize_object(olist);
    free_objectList(olist);
}

/*
使用的测试样例：
{
    "min_position": 9,
    "has_more_items": false,
    "items_html": "Car\t\\",
    "new_latent_count": 6.0,
    "array":["string",5e-2,true,null],
    "object":{
        "min_position": 9.2e+4,
        "has_more_items": false,
        "items_html": "Car"
    }
}
*/