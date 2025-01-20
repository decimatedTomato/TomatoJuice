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
    # for clang
    # export ASAN_SYMBOLIZER_PATH=/usr/bin/llvm-symbolizer
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
    )
endif (UNIX)
if (WIN32)
    target_compile_options(
        tomato_s8
        PRIVATE /INCREMENTAL:NO
        PRIVATE /fsanitize=address
    )
    # string(REPLACE "/RTC1" "" CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
    # set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -fno-omit-frame-pointer")
endif (WIN32)

target_compile_options(
    tomato_s8
    PRIVATE -fsanitize=address
    PRIVATE -D_FORTIFY_SOURCE=2
)


