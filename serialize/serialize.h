//
// Created by xiaoxi on 2023/10/16.
//



#ifndef JSONLIB_SERIALIZE_H
#define JSONLIB_SERIALIZE_H

#include <stdio.h>
#include "common/common.h"
void serialize_init(FILE* orgin);
void serialize_object(ObjectList* oList);
void serialize_number(double num);
void serialize_constant(ValueNode* node);
void serialize_array(ArrayList* aList);
void serialize_string(char* str);
#endif //JSONLIB_SERIALIZE_H


