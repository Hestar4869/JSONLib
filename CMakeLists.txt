cmake_minimum_required(VERSION 3.26)
project(JSONLib C)

set(CMAKE_C_STANDARD 11)
include_directories(${PROJECT_SOURCE_DIR})
add_executable(JSONLib main.c
        common/common.h
        parse/parse.c
        parse/parse.h
        common/error.h)
add_library(parse SHARED parse/parse.c parse/parse.h)
add_executable(test_parse_string test/test_parse_string.c)
target_link_libraries(test_parse_string parse)
