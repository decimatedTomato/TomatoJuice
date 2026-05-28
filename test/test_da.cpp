#include "gtest/gtest.h"

extern "C"
{
#include "tomato_defines.h"
#include "tomato_dynarray.h"

#include "test_da.c"
}

struct Person
{
    const char *name;
    i32         year_of_birth;
    double      height;
};

TOMATO_DYNARRAY_INSTANTIATE(i32, i32);
// TOMATO_DYNARRAY_INSTANTIATE(Person, person);

TEST(dac, All)
{
    EXPECT_FALSE(test_da_append_size_increases());
    EXPECT_FALSE(test_da_get_fails());
    EXPECT_FALSE(test_da_get_succeeds());
    EXPECT_FALSE(test_da_pop_fails());
    EXPECT_FALSE(test_da_pop_succeeds());
    EXPECT_FALSE(test_da_shrink_fails());
    EXPECT_FALSE(test_da_shrink_succeeds());
    EXPECT_FALSE(test_da_insert_fails());
    EXPECT_FALSE(test_da_insert_succeeds());
    EXPECT_FALSE(test_da_foreach());
}

TEST(daappend, SizeIncreases)
{
    const int           array_len{10};
    tomato_dynarray_i32 nums{};
    for (i32 i{}; i < array_len; i++)
    {
        tomato_dynarray_i32_append(&nums, i);
    }
    ASSERT_EQ(nums.size, array_len);
    ASSERT_GE(nums.capacity, array_len);
    tomato_dynarray_i32_free(&nums);
}
