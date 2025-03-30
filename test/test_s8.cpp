#include <stdlib.h>

#include "gtest/gtest.h"
#include <gtest/gtest.h>

extern "C"
{
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
    const s8    str_empty = s8_init(allocated_len, malloc);
    const char  data[allocated_len]{0};
    EXPECT_EQ(memcmp(str_empty, data, strlen(str_empty)), 0);
    EXPECT_EQ(s8_capacity(str_empty), allocated_len);
    s8_free(str_empty, free);
}

TEST(s8from, FromStringLargerThanBuffer)
{
    const usize allocated_len = 64;
    EXPECT_LT(allocated_len, sizeof(FROST_POEM));
    const s8 poem_truncated = s8_from(allocated_len, FROST_POEM, malloc);
    EXPECT_EQ(s8_capacity(poem_truncated), allocated_len);
    EXPECT_EQ(memcmp(poem_truncated, FROST_POEM, allocated_len), 0);
    EXPECT_EQ(poem_truncated[allocated_len], '\0');
    EXPECT_NE(poem_truncated[allocated_len], FROST_POEM[allocated_len]);
    s8_free(poem_truncated, free);
}

TEST(s8from, FromStringEquallySizedToBuffer)
{
    const usize allocated_len = lengthof(FROST_POEM);
    const s8    poem_snug = s8_from(allocated_len, FROST_POEM, malloc);
    EXPECT_EQ(s8_capacity(poem_snug), allocated_len);
    EXPECT_EQ(memcmp(poem_snug, FROST_POEM, allocated_len), 0);
    EXPECT_EQ(poem_snug[allocated_len], '\0');
    EXPECT_EQ(poem_snug[allocated_len], FROST_POEM[allocated_len]);
    s8_free(poem_snug, free);
}

TEST(s8from, FromStringSmallerThanBuffer)
{
    const usize allocated_len = sizeof(FROST_POEM) + 32;
    const s8    poem_extraneous = s8_from(allocated_len, FROST_POEM, malloc);
    EXPECT_EQ(s8_capacity(poem_extraneous), allocated_len);
    EXPECT_EQ(memcmp(poem_extraneous, FROST_POEM, sizeof(FROST_POEM)), 0);
    s8_free(poem_extraneous, free);
}

TEST(s8clone, String)
{
    const s8 poem = S8(FROST_POEM, malloc);
    const s8 forgery = s8_clone(poem, malloc);
    EXPECT_EQ(memcmp(poem, forgery, sizeof(FROST_POEM)), 0);
    EXPECT_EQ(s8_capacity(poem), s8_capacity(forgery));
    EXPECT_NE(poem, forgery);
    s8_free(forgery, free);
    s8_free(poem, free);
}

TEST(s8clone, EmptyString)
{
    const s8 nothing = S8("", malloc);
    const s8 empty = s8_clone(nothing, malloc);
    EXPECT_EQ(nothing[0], 0);
    EXPECT_EQ(s8_capacity(nothing), 0);
    s8_free(empty, free);
    s8_free(nothing, free);
}

void test_free_injection(void *ptr)
{
    const char data[sizeof(FROST_POEM)]{};
    EXPECT_EQ(memcmp(ptr, data, sizeof(FROST_POEM)), 0);
    EXPECT_EQ(*(static_cast<usize *>(ptr) - 1), 0);
    free(ptr);
}

/**
 * This is a black box test, using some knowledge of the implementation of s8.
 * Assumes that the implemenation contains a size_t right before the pointer.
 */
TEST(s8free, FreedMemoryZeroed)
{
    const s8   poem = S8(FROST_POEM, malloc);
    const char data[sizeof(FROST_POEM)]{};
    EXPECT_NE(memcmp(poem, data, sizeof(FROST_POEM)), 0);
    EXPECT_NE(s8_capacity(poem), 0);
    s8_free(poem, test_free_injection);
}

TEST(s8capacity, StringLiteral)
{
    s8 poem = S8(FROST_POEM, malloc);
    EXPECT_EQ(s8_capacity(poem), lengthof(FROST_POEM));
    s8_free(poem, free);
}

TEST(s8capacity, EmptyString)
{
    s8 empty = S8("", malloc);
    EXPECT_EQ(s8_capacity(empty), 0);
    s8_free(empty, free);
}

TEST(s8cmp, EmptyStrings)
{
    s8 empty = S8("", malloc);
    EXPECT_EQ(s8_cmp(empty, empty), 0);
    s8_free(empty, free);
}

TEST(s8cmp, EmptyString)
{
    s8 poem = S8(FROST_POEM, malloc);
    s8 empty = S8("", malloc);
    EXPECT_GT(s8_cmp(poem, empty), 0);
    s8_free(empty, free);
    s8_free(poem, free);
}

TEST(s8cmp, Strings)
{
    s8 poem_frost = S8(FROST_POEM, malloc);
    s8 poem_gilpin = S8(GILPIN_POEM, malloc);
    EXPECT_GT(s8_cmp(poem_frost, poem_gilpin), 0);
    EXPECT_LT(s8_cmp(poem_gilpin, poem_frost), 0);
    s8_free(poem_gilpin, free);
    s8_free(poem_frost, free);
}

TEST(s8cmp, SameLengthStrings)
{
    s8 poem_frost = s8_from(64, FROST_POEM, malloc);
    s8 poem_gilpin = s8_from(64, GILPIN_POEM, malloc);
    EXPECT_GT(s8_cmp(poem_frost, poem_gilpin), 0);
    EXPECT_LT(s8_cmp(poem_gilpin, poem_frost), 0);
    s8_free(poem_gilpin, free);
    s8_free(poem_frost, free);
}

TEST(s8cmp, TruncatedString)
{
    s8 poem = S8(FROST_POEM, malloc);
    s8 poem_truncated = s8_from(64, FROST_POEM, malloc);
    EXPECT_GT(s8_cmp(poem, poem_truncated), 0);
    EXPECT_LT(s8_cmp(poem_truncated, poem), 0);
    s8_free(poem_truncated, free);
    s8_free(poem, free);
}

TEST(s8eq, EmptyStrings)
{
    s8 empty = S8("", malloc);
    EXPECT_TRUE(s8_eq(empty, empty));
    s8_free(empty, free);
}

TEST(s8eq, EmptyString)
{
    s8 poem = S8(FROST_POEM, malloc);
    s8 empty = S8("", malloc);
    EXPECT_FALSE(s8_eq(poem, empty));
    s8_free(empty, free);
    s8_free(poem, free);
}

TEST(s8eq, Strings)
{
    s8 poem_frost = S8(FROST_POEM, malloc);
    s8 poem_gilpin = S8(GILPIN_POEM, malloc);
    EXPECT_FALSE(s8_eq(poem_gilpin, poem_frost));
    s8_free(poem_gilpin, free);
    s8_free(poem_frost, free);
}

TEST(s8eq, SameLengthStrings)
{
    s8 poem_frost = s8_from(64, FROST_POEM, malloc);
    s8 poem_gilpin = s8_from(64, GILPIN_POEM, malloc);
    EXPECT_FALSE(s8_eq(poem_frost, poem_gilpin));
    s8_free(poem_gilpin, free);
    s8_free(poem_frost, free);
}

TEST(s8eq, TruncatedString)
{
    s8 poem = S8(FROST_POEM, malloc);
    s8 poem_truncated = s8_from(64, FROST_POEM, malloc);
    EXPECT_FALSE(s8_eq(poem, poem_truncated));
    s8_free(poem_truncated, free);
    s8_free(poem, free);
}

TEST(s8fill, EmptyString)
{
    s8 empty = S8("", malloc);
    s8_fill(empty, 0xFF);
    EXPECT_EQ(empty[0], '\0');
    s8_free(empty, free);
}

TEST(s8fill, String)
{
    const usize len = 64;
    const s8    str = s8_init(len, malloc);
    const char  data[len]{};
    s8_fill(str, 0xFF);
    EXPECT_NE(memcmp(str, data, len), 0);
    s8_fill(str, 0x00);
    EXPECT_EQ(memcmp(str, data, len), 0);
    s8_free(str, free);
}