set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
add_compile_options(-Wno-character-conversion)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         v1.15.2
    SOURCE_DIR      googletest
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)
