#include "tomato_string.h"

#include <stdio.h>
#include <string.h>

// Uses a private owning struct
typedef struct
{
    usize len;
    char  str[];
} s8_owning;

s8 s8_init(usize len)
{
    s8_owning *string = TOMATO_STRING_ALLOC(sizeof(s8_owning) + len + 1);
    string->len = len;
    return string->str;
}

void s8_free(s8 str)
{
    memset((s8_owning *)(str)-1, 0, s8_len(str) + sizeof(s8_owning));
    TOMATO_STRING_FREE((s8_owning *)(str)-1);
}

s8 s8_from(usize len, const char *src)
{
    s8 out = s8_init(len);
    memcpy(out, src, len);
    return out;
}

usize s8_len(s8 str)
{
    return (((s8_owning *)(str)) - 1)->len;
}

i32 s8_cmp(s8 str1, s8 str2)
{
    usize     size1 = s8_len(str1);
    usize     size2 = s8_len(str2);
    ptrdiff_t size_diff = size1 - size2;
    if (size_diff == 0)
    {
        return memcmp(str1, str2, s8_len(str1));
    }
    i32 shared_length_cmp = memcmp(str1, str2, (size_diff > 0) ? size2 : size1);
    if (shared_length_cmp != 0)
        return shared_length_cmp;
    return size_diff;
}

b32 s8_eq(s8 str1, s8 str2)
{
    if (s8_len(str1) != s8_len(str2))
        return false;
    return memcmp(str1, str2, s8_len(str1)) == 0;
}

s8 s8_concat(s8 str1, s8 str2)
{
    s8 out = s8_init(s8_len(str1) + s8_len(str2));
    memcpy(out, str1, s8_len(str1));
    memcpy(out + s8_len(str1), str2, s8_len(str2));
    return out;
}

s8 s8_clone(s8 str)
{
    return s8_from(s8_len(str), str);
}

void s8_fill(s8 str, u8 data)
{
    memset(str, data, s8_len(str));
}

i32 s8_print(s8 str)
{
    return printf("%.*s", (i32)s8_len(str), str);
}

i32 s8_debug_print(s8 str)
{
    i32 printed_chars = 0;
    printed_chars += printf("s8(len=%llu, str=\"", s8_len(str));
    for (usize i = 0; i < s8_len(str); i++)
    {
        printf("%2X", str[i] & 0xFF);
    }
    printed_chars += printf("\")");
    return printed_chars + 2 * (i32)s8_len(str);
}