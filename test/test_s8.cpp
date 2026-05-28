#include "gtest/gtest.h"

extern "C"
{
#include "tomato_allocator.h"
#include "tomato_defines.h"
#include "tomato_string.h"
}

// Nothing Gold Can Stay by Robert Frost
#define FROST_POEM                                                                                                     \
    "Nature's first green is gold,\nHer hardest hue to hold.\nHer early leaf's a flower;\nBut only so an hour.\n"      \
    "Then leaf subsides to leaf.\nSo Eden sank to grief,\nSo dawn goes down to day.\nNothing gold can stay.\n"
// Two-Headed Calf by Laura Gilpin
#define GILPIN_POEM                                                                                                    \
    "Tomorrow when the farm boys find this freak of nature, they will wrap his body in newpaper and carry him to the " \
    "museum.\nBut tonight he is alive and in the north field with his mother. It is a perfect evening: the moon "      \
    "rising over the orchard, the wind in the grass.And as he stares into the sky, there are twice as many stars "     \
    "as usual.\n "

TEST(s8init, InitDefault)
{
    const usize allocated_len = 64;
    const s8    str_empty = s8_init(allocated_len, &tomato_libc_malloc_ctx);
    const char  data[allocated_len]{0};
    EXPECT_EQ(memcmp(str_empty, data, strlen(str_empty)), 0);
    EXPECT_EQ(s8_capacity(str_empty), allocated_len);
    s8_free(str_empty, &tomato_libc_malloc_ctx);
}

TEST(s8from, FromStringLargerThanBuffer)
{
    const usize allocated_len = 64;
    EXPECT_LT(allocated_len, sizeof(FROST_POEM));
    const s8 poem_truncated = s8_from(allocated_len, FROST_POEM, &tomato_libc_malloc_ctx);
    EXPECT_EQ(s8_capacity(poem_truncated), allocated_len);
    EXPECT_EQ(memcmp(poem_truncated, FROST_POEM, allocated_len), 0);
    EXPECT_EQ(poem_truncated[allocated_len], '\0');
    EXPECT_NE(poem_truncated[allocated_len], FROST_POEM[allocated_len]);
    s8_free(poem_truncated, &tomato_libc_malloc_ctx);
}

TEST(s8from, FromStringEquallySizedToBuffer)
{
    const usize allocated_len = lengthof(FROST_POEM);
    const s8    poem_snug = s8_from(allocated_len, FROST_POEM, &tomato_libc_malloc_ctx);
    EXPECT_EQ(s8_capacity(poem_snug), allocated_len);
    EXPECT_EQ(memcmp(poem_snug, FROST_POEM, allocated_len), 0);
    EXPECT_EQ(poem_snug[allocated_len], '\0');
    EXPECT_EQ(poem_snug[allocated_len], FROST_POEM[allocated_len]);
    s8_free(poem_snug, &tomato_libc_malloc_ctx);
}

TEST(s8from, FromStringSmallerThanBuffer)
{
    const usize allocated_len = sizeof(FROST_POEM) + 32;
    const s8    poem_extraneous = s8_from(allocated_len, FROST_POEM, &tomato_libc_malloc_ctx);
    EXPECT_EQ(s8_capacity(poem_extraneous), allocated_len);
    EXPECT_EQ(memcmp(poem_extraneous, FROST_POEM, sizeof(FROST_POEM)), 0);
    s8_free(poem_extraneous, &tomato_libc_malloc_ctx);
}

TEST(s8clone, String)
{
    const s8 poem = S8(FROST_POEM, &tomato_libc_malloc_ctx);
    const s8 forgery = s8_clone(poem, &tomato_libc_malloc_ctx);
    EXPECT_EQ(memcmp(poem, forgery, sizeof(FROST_POEM)), 0);
    EXPECT_EQ(s8_capacity(poem), s8_capacity(forgery));
    EXPECT_NE(poem, forgery);
    s8_free(forgery, &tomato_libc_malloc_ctx);
    s8_free(poem, &tomato_libc_malloc_ctx);
}

TEST(s8clone, EmptyString)
{
    const s8 nothing = S8("", &tomato_libc_malloc_ctx);
    const s8 empty = s8_clone(nothing, &tomato_libc_malloc_ctx);
    EXPECT_EQ(nothing[0], 0);
    EXPECT_EQ(s8_capacity(nothing), 0);
    s8_free(empty, &tomato_libc_malloc_ctx);
    s8_free(nothing, &tomato_libc_malloc_ctx);
}

/**
 * This is a black box test, using some knowledge of the implementation of s8.
 * Assumes that the implemenation contains a size_t right before the pointer.
 */
TEST(s8free, FreedMemoryZeroed)
{
    const auto wrapped_malloc = [](usize size, void *) { return std::malloc(size); };
    const auto checked_free = [](void *buffer, void *) {
        const usize allocation_size = sizeof(usize) + sizeof(FROST_POEM);
        const char  data[allocation_size]{};
        EXPECT_EQ(memcmp(buffer, data, allocation_size), 0);
        std::free(buffer);
    };
    tomato_alloc_ctx zero_checker{wrapped_malloc, checked_free, nullptr};
    const s8         poem = S8(FROST_POEM, &zero_checker);
    const char       data[sizeof(FROST_POEM)]{};
    EXPECT_NE(memcmp(poem, data, sizeof(FROST_POEM)), 0);
    EXPECT_NE(s8_capacity(poem), 0);
    s8_free(poem, &zero_checker);
}

TEST(s8capacity, StringLiteral)
{
    s8 poem = S8(FROST_POEM, &tomato_libc_malloc_ctx);
    EXPECT_EQ(s8_capacity(poem), lengthof(FROST_POEM));
    s8_free(poem, &tomato_libc_malloc_ctx);
}

TEST(s8capacity, EmptyString)
{
    s8 empty = S8("", &tomato_libc_malloc_ctx);
    EXPECT_EQ(s8_capacity(empty), 0);
    s8_free(empty, &tomato_libc_malloc_ctx);
}

TEST(s8cmp, EmptyStrings)
{
    s8 empty = S8("", &tomato_libc_malloc_ctx);
    EXPECT_EQ(s8_cmp(empty, empty), 0);
    s8_free(empty, &tomato_libc_malloc_ctx);
}

TEST(s8cmp, EmptyString)
{
    s8 poem = S8(FROST_POEM, &tomato_libc_malloc_ctx);
    s8 empty = S8("", &tomato_libc_malloc_ctx);
    EXPECT_GT(s8_cmp(poem, empty), 0);
    s8_free(empty, &tomato_libc_malloc_ctx);
    s8_free(poem, &tomato_libc_malloc_ctx);
}

TEST(s8cmp, Strings)
{
    s8 poem_frost = S8(FROST_POEM, &tomato_libc_malloc_ctx);
    s8 poem_gilpin = S8(GILPIN_POEM, &tomato_libc_malloc_ctx);
    EXPECT_LT(s8_cmp(poem_frost, poem_gilpin), 0);
    EXPECT_GT(s8_cmp(poem_gilpin, poem_frost), 0);
    s8_free(poem_gilpin, &tomato_libc_malloc_ctx);
    s8_free(poem_frost, &tomato_libc_malloc_ctx);
}

TEST(s8cmp, SameLengthStrings)
{
    s8 poem_frost = s8_from(64, FROST_POEM, &tomato_libc_malloc_ctx);
    s8 poem_gilpin = s8_from(64, GILPIN_POEM, &tomato_libc_malloc_ctx);
    EXPECT_LT(s8_cmp(poem_frost, poem_gilpin), 0);
    EXPECT_GT(s8_cmp(poem_gilpin, poem_frost), 0);
    s8_free(poem_gilpin, &tomato_libc_malloc_ctx);
    s8_free(poem_frost, &tomato_libc_malloc_ctx);
}

TEST(s8cmp, TruncatedString)
{
    s8 poem = S8(FROST_POEM, &tomato_libc_malloc_ctx);
    s8 poem_truncated = s8_from(64, FROST_POEM, &tomato_libc_malloc_ctx);
    EXPECT_GT(s8_cmp(poem, poem_truncated), 0);
    EXPECT_LT(s8_cmp(poem_truncated, poem), 0);
    s8_free(poem_truncated, &tomato_libc_malloc_ctx);
    s8_free(poem, &tomato_libc_malloc_ctx);
}

TEST(s8eq, EmptyStrings)
{
    s8 empty = S8("", &tomato_libc_malloc_ctx);
    EXPECT_TRUE(s8_eq(empty, empty));
    s8_free(empty, &tomato_libc_malloc_ctx);
}

TEST(s8eq, EmptyString)
{
    s8 poem = S8(FROST_POEM, &tomato_libc_malloc_ctx);
    s8 empty = S8("", &tomato_libc_malloc_ctx);
    EXPECT_FALSE(s8_eq(poem, empty));
    s8_free(empty, &tomato_libc_malloc_ctx);
    s8_free(poem, &tomato_libc_malloc_ctx);
}

TEST(s8eq, Strings)
{
    s8 poem_frost = S8(FROST_POEM, &tomato_libc_malloc_ctx);
    s8 poem_gilpin = S8(GILPIN_POEM, &tomato_libc_malloc_ctx);
    EXPECT_FALSE(s8_eq(poem_gilpin, poem_frost));
    s8_free(poem_gilpin, &tomato_libc_malloc_ctx);
    s8_free(poem_frost, &tomato_libc_malloc_ctx);
}

TEST(s8eq, SameLengthStrings)
{
    s8 poem_frost = s8_from(64, FROST_POEM, &tomato_libc_malloc_ctx);
    s8 poem_gilpin = s8_from(64, GILPIN_POEM, &tomato_libc_malloc_ctx);
    EXPECT_FALSE(s8_eq(poem_frost, poem_gilpin));
    s8_free(poem_gilpin, &tomato_libc_malloc_ctx);
    s8_free(poem_frost, &tomato_libc_malloc_ctx);
}

TEST(s8eq, TruncatedString)
{
    s8 poem = S8(FROST_POEM, &tomato_libc_malloc_ctx);
    s8 poem_truncated = s8_from(64, FROST_POEM, &tomato_libc_malloc_ctx);
    EXPECT_FALSE(s8_eq(poem, poem_truncated));
    s8_free(poem_truncated, &tomato_libc_malloc_ctx);
    s8_free(poem, &tomato_libc_malloc_ctx);
}

TEST(s8fill, EmptyString)
{
    s8 empty = S8("", &tomato_libc_malloc_ctx);
    s8_fill(empty, 0xFF);
    EXPECT_EQ(empty[0], '\0');
    s8_free(empty, &tomato_libc_malloc_ctx);
}

TEST(s8fill, String)
{
    const usize len = 64;
    const s8    str = s8_init(len, &tomato_libc_malloc_ctx);
    const char  data[len]{};
    s8_fill(str, 0xFF);
    EXPECT_NE(memcmp(str, data, len), 0);
    s8_fill(str, 0x00);
    EXPECT_EQ(memcmp(str, data, len), 0);
    s8_free(str, &tomato_libc_malloc_ctx);
}