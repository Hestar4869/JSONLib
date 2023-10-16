//
// Created by xiaoxi on 2023/10/16.
//
#include <serialize/serialize.h>
#include <parse/parse.h>
int main(){
    parse_init(stdin);
    ObjectList* oList = parse_object();
    serialize_init(stdout);
    serialize_object(oList);
}

/*
{
    "min_position": 9,
    "has_more_items": false,
    "items_html": "Car",
    "new_latent_count": 6,
    "array":["string",5e-2,true,null],
    "object":{
        "min_position": 9,
        "has_more_items": false,
        "items_html": "Car"
    }
}
*/