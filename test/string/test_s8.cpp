extern "C"
{
#include "tomato_string.h"
}

// https://github.com/google/sanitizers/wiki/AddressSanitizer/000d3f9655b81a6f661277d3ab8716826a237309
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

/* Try doing this in a setup fixture struct */
// auto dangerous_operation(s8 const &str, const usize str_size) -> void
// {
//     const usize *str_len = reinterpret_cast<usize *>(str) - 1;
//     const char   data[str_size]{};
//     s8_free(str);
//     EXPECT_EQ(*str_len, 0);
//     EXPECT_EQ(memcmp(str, data, str_size), 0);
// }
struct S8_free : public testing::Test
{
  protected:
    ATTRIBUTE_NO_SANITIZE_ADDRESS
    void TearDown() override
    {
        EXPECT_EQ(*poem_len, 0);
        EXPECT_EQ(memcmp(poem, data, 205), 0);
    }
    const s8 poem =
        S8("Nature's first green is gold,\nHer hardest hue to hold.\nHer early leaf's a flower;\nBut only so an "
           "hour.\nThen leaf subsides to leaf.\nSo Eden sank to grief,\nSo dawn goes down to day.\nNothing gold can "
           "stay.\n");
    const usize *poem_len = reinterpret_cast<usize *>(poem) - 1;
    const char   data[204]{};
};
TEST_F(S8_free, Memory_zeroed)
{
    EXPECT_EQ(*poem_len, 203);
    EXPECT_NE(memcmp(poem, data, 204), 0);
    s8_free(poem);
}