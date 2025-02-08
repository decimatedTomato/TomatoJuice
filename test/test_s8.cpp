#include <stdlib.h>

#include "gtest/gtest.h"
#include <gtest/gtest.h>

#include "tomato_defines.h"

#pragma region whitebox_tests_setup
#define SAMPLE_TEXT                                                                                                    \
    "Nature's first green is gold,\nHer hardest hue to hold.\nHer early leaf's a flower;\nBut only so an "             \
    "hour.\nThen leaf subsides to leaf.\nSo Eden sank to grief,\nSo dawn goes down to day.\nNothing gold can "         \
    "stay.\n"

void test_free_injection(void *ptr)
{
    const char data[sizeof(SAMPLE_TEXT)]{};
    EXPECT_EQ(memcmp(ptr, data, sizeof(SAMPLE_TEXT)), 0);
    EXPECT_EQ(*(static_cast<usize *>(ptr) - 1), 0);
    free(ptr);
}
#define TOMATO_STRING_ALLOC(X) calloc(X, sizeof(char))
#define TOMATO_STRING_FREE test_free_injection
#pragma endregion white_box_tests_setup

extern "C"
{
#include "tomato_string.h"
}

#pragma region whitebox_tests
TEST(S8free, FreedMemoryZeroed)
{
    const s8   poem = S8(SAMPLE_TEXT);
    const char data[sizeof(SAMPLE_TEXT)]{};
    EXPECT_NE(memcmp(poem, data, sizeof(SAMPLE_TEXT)), 0);
    EXPECT_NE(s8_len(poem), 0);
    s8_free(poem);
}
#pragma endregion whitebox_tests

#pragma region blackbox_tests
TEST(S8init, DefaultConstruction)
{
    const usize allocated_len = 64;
    const s8    str_empty = s8_init(allocated_len);
    const char  data[allocated_len]{};
    EXPECT_FALSE(!str_empty);
    EXPECT_EQ(memcmp(str_empty, data, allocated_len), 0);
    EXPECT_EQ(s8_len(str_empty), allocated_len);
    s8_free(str_empty);
}
#pragma endregion
