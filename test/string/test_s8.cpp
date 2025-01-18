extern "C"
{
#include "tomato_string.h"
}

#include <gtest/gtest.h>
#include <string.h>

TEST(S8_init, Underlying_data)
{
    const usize allocated_len = 64;
    const s8    str = s8_init(allocated_len);
    const char  data[allocated_len]{};
    EXPECT_FALSE(!str);
    EXPECT_EQ(memcmp(str, data, allocated_len), 0);
    EXPECT_EQ(*(reinterpret_cast<size_t *>(str) - 1), allocated_len);
}

TEST(S8_free, Memory_zeroed)
{
    const s8 poem =
        S8("Nature's first green is gold,\nHer hardest hue to hold.\nHer early leaf's a flower;\nBut only so an "
           "hour.\nThen leaf subsides to leaf.\nSo Eden sank to grief,\nSo dawn goes down to day.\nNothing gold can "
           "stay.\n");
    const char   data[sizeof(poem)]{};
    const usize *poem_len = (reinterpret_cast<size_t *>(poem) - 1);
    s8_free(poem);
    EXPECT_EQ(*poem_len, 0); // FIXME use after free?
    EXPECT_EQ(memcmp(poem, data, sizeof(poem)), 0);
}