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

if (UNIX)
    target_link_options(
        tomato_s8
        PUBLIC -fsanitize=address
    )
    target_compile_options(
        tomato_s8
        PRIVATE -Werror
        PRIVATE -Wextra
        PRIVATE -Wall
        PRIVATE -pedantic
        PRIVATE -D_FORTIFY_SOURCE=2
    )
    # export ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer# for clang
endif (UNIX)
if (WIN32)
    target_compile_options(
        tomato_s8
        PRIVATE /fsanitize=address
        PRIVATE /Zi
    )
endif (WIN32)
