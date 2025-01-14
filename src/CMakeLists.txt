cmake_minimum_required(VERSION 3.22)
project(tomato_juice)

include_directories(
    ./common/
    ./string/
)

add_library(
    tomato_s8
    string/tomato_string.c
)
