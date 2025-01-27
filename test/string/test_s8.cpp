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

/* Should there really be a unit test that takes this white box approach?
 * This test will fail if I ever change the underlying memory layout, even if that is an intentional change
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

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <crtdbg.h>
#include <windows.h>
#include <winnt.h>

volatile long g_alloc_depth = 0;
int           MyAllocHook(
              int                  allocType,
              void                *userData,
              size_t               size,
              int                  blockType,
              long                 requestNumber,
              const unsigned char *filename,
              int                  lineNumber)
{
    if (blockType == _CRT_BLOCK)
    {
        return 1;
    }
    if (InterlockedIncrement(&g_alloc_depth) > 1)
    {
        InterlockedDecrement(&g_alloc_depth);
        return 1;
    }
    if (allocType == _HOOK_FREE)
    {
        const char data[sizeof(SAMPLE_TEXT)]{};
        EXPECT_EQ(memcmp(userData, data, sizeof(SAMPLE_TEXT)), 0);
        EXPECT_EQ(s8_len(static_cast<s8>(userData)), 0);
    }
    InterlockedDecrement(&g_alloc_depth);
    return 1;
}
TEST(S8_free, Memory_zeroed)
{
    const s8   poem = S8(SAMPLE_TEXT);
    const char data[sizeof(SAMPLE_TEXT)]{};
    EXPECT_NE(memcmp(poem, data, sizeof(SAMPLE_TEXT)), 0);
    EXPECT_NE(s8_len(poem), 0); // FIXME is this the right cast?
    _CRT_ALLOC_HOOK previous_alloc_hook = _CrtSetAllocHook(MyAllocHook);
    s8_free(poem);
    _CrtSetAllocHook(previous_alloc_hook);
}
#endif
#ifdef __GNUC__
TEST(S8_free, Memory_zeroed)
{
    const s8   poem = S8(SAMPLE_TEXT);
    const char data[sizeof(SAMPLE_TEXT)]{};
    EXPECT_NE(memcmp(poem, data, sizeof(SAMPLE_TEXT)), 0);
    EXPECT_NE(s8_len(poem), 0);
    // TODO dylsm
    s8_free(poem);
    ASSERT_FALSE(1);
}
#endif