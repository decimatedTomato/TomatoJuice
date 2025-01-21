cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# string(REGEX REPLACE "/RTC(su|[1su])" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
project(test_tomato_juice)

add_subdirectory(../src ../../src/build)

include_directories(
    ${PROJECT_SOURCE_DIR}/../src/common/
    ${PROJECT_SOURCE_DIR}/../src/string/
)

add_executable(
    ${PROJECT_NAME}
    string/test_s8.cpp
)

if (WIN32)
    add_compile_definitions(
        _DISABLE_VECTOR_ANNOTATION
    )
    add_compile_options(
        /fsanitize=address
        /Zi
    )
endif (WIN32)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         v1.15.2
    SOURCE_DIR      googletest
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE GTest::gtest_main
    PRIVATE tomato_s8
)

enable_testing()
gtest_discover_tests(${PROJECT_NAME})
