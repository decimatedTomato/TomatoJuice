#include "gtest/gtest.h"

extern "C"
{
#include "tomato_defines.h"
#include "tomato_dynarray.h"
}

struct Person
{
    const char *name;
    i32         year_of_birth;
    double      height;
};

TOMATO_DYNARRAY_INSTANTIATE(i32, i);
TOMATO_DYNARRAY_INSTANTIATE(Person, person);

TEST(daappend, SizeIncreases)
{
    const int         array_len{10};
    tomato_dynarray_i nums{};
    for (i32 i{}; i < array_len; i++)
    {
        tomato_dynarray_append_i(&nums, i);
    }
    ASSERT_EQ(nums.size, array_len);
    ASSERT_GE(nums.capacity, array_len);
    tomato_dynarray_free_i(&nums);
}
