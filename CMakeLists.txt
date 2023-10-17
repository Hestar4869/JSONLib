cmake_minimum_required(VERSION 3.26)
project(JSONLib C)

set(CMAKE_C_STANDARD 11)
include_directories(${PROJECT_SOURCE_DIR})

add_library(parse SHARED parse/parse.c parse/parse.h common/common.c )
add_library(serialize SHARED serialize/serialize.c serialize/serialize.h common/common.c)


add_executable(test_parse_string test/test_parse_string.c)
target_link_libraries(test_parse_string parse)

add_executable(test_parse_array test/test_parse_array.c)
target_link_libraries(test_parse_array parse)

add_executable(test_parse_object test/test_parse_object.c)
target_link_libraries(test_parse_object parse)


add_executable(test_serialize test/test_serialize.c)
target_link_libraries(test_serialize serialize parse)

add_executable(test_CRUD test/test_CRUD.c)
target_link_libraries(test_CRUD serialize parse)
