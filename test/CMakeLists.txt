cmake_minimum_required(VERSION 3.22)
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
    # see https://developercommunity.visualstudio.com/t/Enabling-Address-Sanitizer-results-in-er/10053975?space=61&entry=problem&q=VSIX+project+doesn%27t+load+well+in+SSMS&scope=follow
    add_compile_definitions(
        _DISABLE_VECTOR_ANNOTATION
        _DISABLE_STRING_ANNOTATION
    )
endif (WIN32)

set(CMAKE_CXX_STANDARD 14)
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
    PRIVATE tomato_s8
)

enable_testing()
gtest_discover_tests(${PROJECT_NAME})
