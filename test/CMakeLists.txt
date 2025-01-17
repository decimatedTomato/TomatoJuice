cmake_minimum_required(VERSION 3.22)
project(test_tomato_juice)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(../src ../../src/build)
add_subdirectory(vendor)

include_directories(
    ${PROJECT_SOURCE_DIR}/../src/common/
    ${PROJECT_SOURCE_DIR}/../src/string/
)

add_executable(
    ${PROJECT_NAME}
    string/test_s8.cpp
)

# target_compile_options(
#     ${PROJECT_NAME}
#     PRIVATE -g
# )

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE GTest::gtest_main
    PRIVATE tomato_s8
)

include(GoogleTest)

enable_testing()
gtest_discover_tests(${PROJECT_NAME})
