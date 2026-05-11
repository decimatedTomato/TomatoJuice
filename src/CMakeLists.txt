cmake_minimum_required(VERSION 3.22)
project(tomato_juice_src LANGUAGES C)

set(CMAKE_C_STANDARD 23)

add_library(tomato_allocator tomato_allocator.c)
add_library(tomato_string tomato_string.c tomato_allocator.c)
