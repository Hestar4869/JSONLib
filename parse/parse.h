//
// Created by xiaoxi on 2023/10/12.
//

#ifndef JSONLIB_PARSE_H
#define JSONLIB_PARSE_H
#include<common/common.h>
#include <stdio.h>


bool parse_init(FILE* origin);

/**
 * object
 *      '{' ws '}'
 *      '{' ws value ws '}'
 * @return 返回解析后的object集合的头指针
 */
ObjectList* parse_object();

/**
 * 读取并解析字符串,并检测是否构成完备字符串
 * @return 返回一个指向字符串的指针，若不构成完备的字符串，返回NULL
 */
char* parse_string();

/**
 * 读取并解析值类型，并检测是否构成完备值
 * @return 返回具体值以及类型
 */
ValueNode* parse_value();

/**
 * 读取并解析数字类型，并检测是否构成完备值
 * @return 返回一个数字
 */
double parse_number();

/**
 * 读取并解析数组，并检测是否构成完备值
 * @return  返回一个值集合
 */
ArrayList* parse_array();

/**
 * 读取并解析3个常量值true,false,null,并检测是否符合
 * @return 返回常量值的字符串集
 */
char* parse_constant();

/**
 * 持续读入并处理连续空白字符，例如回车、换行。制表符等
 * @return 返回第一个非空白字符的字符
 */
char deal_whitespace();

/**
 * 查看输入缓冲区中下一个字符，但并不改变输入缓冲区中的内容
 * @return 返回输入缓冲区中的下一个字符
 */
char peek_char();


#endif //JSONLIB_PARSE_H
