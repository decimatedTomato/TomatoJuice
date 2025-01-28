cmake_minimum_required(VERSION 3.22)
project(tomato_juice)

add_library(
    tomato_s8
    tomato_string.h
)

if (UNIX)
    target_compile_options(
        tomato_s8
        PUBLIC -fsanitize=address
        PRIVATE -Werror
        PRIVATE -Wextra
        PRIVATE -Wall
        PRIVATE -pedantic
        PRIVATE -D_FORTIFY_SOURCE=2
    )
endif (UNIX)
# if (WIN32)
#     target_compile_options(
#         tomato_s8
#         PRIVATE /Wall
#     )
# endif (WIN32)
