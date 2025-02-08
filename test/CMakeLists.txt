cmake_minimum_required(VERSION 3.22)
project(test_tomato_juice)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

# Consider making build with asan a flag

set(
    TOMATO_JUICE_DIR
    ${PROJECT_SOURCE_DIR}/../src
)

add_executable(
    ${PROJECT_NAME}
    ${PROJECT_SOURCE_DIR}/test_s8.cpp
    ${TOMATO_JUICE_DIR}/tomato_defines.h
    ${TOMATO_JUICE_DIR}/tomato_string.h
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE ${TOMATO_JUICE_DIR}
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message( FATAL_ERROR  "Compiler is Clang")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message( STATUS "Compiler is GNU")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # message( STATUS "Compiler is MSVC")
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE /fsanitize=address
    )
    target_link_options(
        ${PROJECT_NAME}
        PRIVATE /DEBUG:FULL
        PRIVATE /INCREMENTAL:NO
    )
    target_compile_definitions(
        ${PROJECT_NAME}
        PRIVATE _DISABLE_VECTOR_ANNOTATION
        PRIVATE _DISABLE_STRING_ANNOTATION
    )
endif()
# if (WIN32)
#     # see https://developercommunity.visualstudio.com/t/Enabling-Address-Sanitizer-results-in-er/10053975?space=61&entry=problem&q=VSIX+project+doesn%27t+load+well+in+SSMS&scope=follow
#     # add_link_options(
#     #     /INCREMENTAL:NO
#     # )
# endif (WIN32)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         v1.15.2
    SOURCE_DIR      googletest
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE GTest::gtest_main
)
enable_testing()
gtest_discover_tests(${PROJECT_NAME})
