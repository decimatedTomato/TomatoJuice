cmake_minimum_required(VERSION 3.22)
project(tomato_juice_test LANGUAGES CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

set(TOMATO_SRC_DIR ../src)

add_executable(
    test_tomato_juice
    ${PROJECT_SOURCE_DIR}/test_s8.cpp
)

target_include_directories(
    test_tomato_juice
    PRIVATE ${TOMATO_SRC_DIR}
)

include(gtest.cmake)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(FATAL_ERROR  "Compiler is Clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Compiler is GNU")
    target_compile_options(
        test_tomato_juice
        PRIVATE -fsanitize=address
    )
    target_link_options(
        test_tomato_juice
        PRIVATE -fsanitize=address
    )
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Compiler is MSVC")
    target_compile_options(
        test_tomato_juice
        PRIVATE /fsanitize=address
    )
    target_link_options(
        test_tomato_juice
        PRIVATE /DEBUG:FULL
    )
endif()

target_link_libraries(
    test_tomato_juice
    PRIVATE tomato_string
    PRIVATE GTest::gtest_main
)
gtest_discover_tests(test_tomato_juice)
