cmake_minimum_required(VERSION 3.22)
project(tomato_juice_test LANGUAGES CXX)

set(TOMATO_INCLUDE_DIR ../include)

add_executable(
    test_tomato_juice
    ${PROJECT_SOURCE_DIR}/test_s8.cpp
    ${PROJECT_SOURCE_DIR}/test_da.cpp
)

target_include_directories(
    test_tomato_juice
    PRIVATE ${TOMATO_INCLUDE_DIR}
)

include(gtest.cmake)
    
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS  "Compiler is Clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Compiler is GNU")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "Compiler is MSVC")
    target_compile_options(
        test_tomato_juice
        PRIVATE /W4
        # PRIVATE /fsanitize=address
    )
endif()
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(
        test_tomato_juice
        PRIVATE -fsanitize=address
        PRIVATE -Wall
        PRIVATE -Wextra
        PRIVATE -Werror
        PRIVATE -pedantic
        PRIVATE -Wno-missing-field-initializers
    )
    target_link_options(
        test_tomato_juice
        PRIVATE -fsanitize=address
    )
endif()

target_link_libraries(
    test_tomato_juice
    PRIVATE tomato_string
    PRIVATE GTest::gtest_main
)
gtest_discover_tests(test_tomato_juice)
