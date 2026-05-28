cmake_minimum_required(VERSION 3.22)
project(tomato_juice_src LANGUAGES C)

set(CMAKE_C_STANDARD 23)

set(TOMATO_INCLUDE_DIR ../include)

add_library(tomato_allocator tomato_allocator.c)
target_include_directories(tomato_allocator PRIVATE ${TOMATO_INCLUDE_DIR})

add_library(tomato_string tomato_string.c tomato_allocator.c)
target_include_directories(tomato_string PRIVATE ${TOMATO_INCLUDE_DIR})

add_library(tomato_arena tomato_arena.c tomato_allocator.c)
target_include_directories(tomato_arena PRIVATE ${TOMATO_INCLUDE_DIR})
