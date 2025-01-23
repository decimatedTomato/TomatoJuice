extern "C"
{
#include "tomato_string.h"
}

#if defined(__clang__) || defined(__GNUC__)
#define ATTRIBUTE_NO_SANITIZE_ADDRESS __attribute__((no_sanitize_address))
#else
#define ATTRIBUTE_NO_SANITIZE_ADDRESS
#endif
#include <gtest/gtest.h>
#include <string.h>

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

#if defined(__clang__) || defined(__GNUC__)
ATTRIBUTE_NO_SANITIZE_ADDRESS
TEST(S8_free, Memory_zeroed)
{
    const s8 poem =
        S8("Nature's first green is gold,\nHer hardest hue to hold.\nHer early leaf's a flower;\nBut only so an "
           "hour.\nThen leaf subsides to leaf.\nSo Eden sank to grief,\nSo dawn goes down to day.\nNothing gold can "
           "stay.\n");
    const char   data[sizeof(poem)]{};
    const usize *poem_len = reinterpret_cast<usize *>(poem) - 1;
    s8_free(poem);
    EXPECT_EQ(*poem_len, 0);
    EXPECT_EQ(memcmp(poem, data, sizeof(poem)), 0);
}
#endif // clang || gnuc