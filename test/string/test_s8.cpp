extern "C"
{
#include "tomato_string.h"
}

#include <gtest/gtest.h>
#include <string.h>


TEST(S8_Interface, Underlying_Datalayout)
{
    const unsigned long long allocated_len = 64;
    unsigned char            data[sizeof(s8_owning) + allocated_len] = {};
    s8_owning *              owning_str = reinterpret_cast<s8_owning *>(data);
    owning_str->len = allocated_len;
    owning_str->str[0] = 'a';
    ASSERT_EQ(owning_str->str[0], 'a');
    ASSERT_EQ(owning_str->str[1], '\0');
    ASSERT_EQ(owning_str->len, allocated_len);
    ASSERT_FALSE(!owning_str);
}

TEST(S8_Interface, Underlying_data_empty_s8)
{
    const unsigned long long allocated_len = 64;
    s8                       str = s8_init(allocated_len);
    ASSERT_FALSE(!str);
    char data[allocated_len]{};
    ASSERT_EQ(memcmp(str, data, allocated_len), 0);
    ASSERT_EQ(reinterpret_cast<s8_owning *>(str)[-1].len, allocated_len);
}