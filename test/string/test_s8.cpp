extern "C"
{
#include "tomato_string.h"
}

#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAMPLE_TEXT                                                                                                    \
    "Nature's first green is gold,\nHer hardest hue to hold.\nHer early leaf's a flower;\nBut only so an "             \
    "hour.\nThen leaf subsides to leaf.\nSo Eden sank to grief,\nSo dawn goes down to day.\nNothing gold can "         \
    "stay.\n"

/* TODO move white box tests to a separate file
 */
TEST(S8_init, Underlying_data)
{
    const usize allocated_len = 64;
    const s8    str_empty = s8_init(allocated_len);
    const char  data[allocated_len]{};
    EXPECT_FALSE(!str_empty);
    EXPECT_EQ(memcmp(str_empty, data, allocated_len), 0);
    EXPECT_EQ(*(reinterpret_cast<size_t *>(str_empty) - 1), allocated_len);
    s8_free(str_empty);
}

#define TEST_FREE_PREVIOUS TOMATO_STRING_FREE
void test_free_injection(void *ptr)
{
    const char data[sizeof(SAMPLE_TEXT)]{};
    EXPECT_EQ(memcmp(ptr, data, sizeof(SAMPLE_TEXT)), 0);
    EXPECT_EQ(s8_len(static_cast<s8>(ptr)), 0);
    TEST_FREE_PREVIOUS(ptr);
}

TEST(S8_free, Memory_zeroed)
{
    const s8   poem = S8(SAMPLE_TEXT);
    const char data[sizeof(SAMPLE_TEXT)]{};
    EXPECT_NE(memcmp(poem, data, sizeof(SAMPLE_TEXT)), 0);
    EXPECT_NE(s8_len(poem), 0);
#undef TOMATO_STRING_FREE
#define TOMATO_STRING_FREE test_free_injection
    s8_free(poem);
#undef TOMATO_STRING_FREE
#define TOMATO_STRING_FREE TEST_FREE_PREVIOUS
#undef TEST_FREE_PREVIOUS
}