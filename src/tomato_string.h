#pragma once

#include "tomato_defines.h"

#include <stdio.h>
#include <string.h>

/* String type that owns its memory, retains null terminator (compatible with string.h) and O(1) check for capacity. */
typedef char *s8;

// TODO make macro prevent pointers from being passed
// TODO write tests for strange values and types being passed into the macro
/* Initializes s8 string the size of src and then copies contents from src.
 * Note: Argument must be a string literal.
 */
#define S8(c_str, alloc) s8_from(lengthof(c_str), (c_str), (alloc))

/* Initializes memory for string of given capacity, using provided allocator.
 * len should not include the null terminator.
 */
s8 s8_init(usize len, tomato_alloc alloc);

/* Initializes and returns string with given capacity, populated with src, using provided allocator.
 * len should not include the null terminator.
 */
s8 s8_from(usize len, const char *src, tomato_alloc alloc);

/* Initializes and returns new string as exact copy of given string using provided allocator. */
s8 s8_clone(s8 str, tomato_alloc alloc);

/* Frees and zeroes out memory from string using provided free function.
 * If nullptr is passed, only zeroes memory.
 */
void s8_free(s8 str, tomato_free free);

/* Returns the capacity of the string.
 * Note: An extra byte is allocated to hold the null terminator, this is not counted.
 */
usize s8_capacity(s8 str);

/* Compares strings lexicographically (uses strcmp but avoids buffer overruns):
 *  Negative if str1 comes earlier alphabetically.
 *  Zero if they are exactly equal.
 *  Positive if str1 comes later alphabetically.
 */
i32 s8_cmp(s8 str1, s8 str2);

/* Determines whether two strings are identical. */
b32 s8_eq(s8 str1, s8 str2);

/* Fills a string up to capacity with one value, excluding the null terminator. */
void s8_fill(s8 str, u8 val);

/* Prints the string to stdout, returns the number of characters printed. */
i32 s8_print(s8 str);

/* Prints a debug representation of the string in hex to provided file,
 * returns the number of characters printed.
 */
i32 s8_debug_print(FILE *file, s8 str);

typedef struct
{
    usize len;
    char  str[];
} internal_s8;

static internal_s8 *get_internal(s8 str)
{
    return ((internal_s8 *)str) - 1;
}

s8 s8_init(usize len, tomato_alloc alloc)
{
    if (alloc == nullptr)
        return nullptr;
    internal_s8 *string = (internal_s8 *)alloc(sizeof(internal_s8) + len + 1);
    if (string == nullptr)
        return nullptr;
    string->len = len;
    string->str[0] = '\0';
    return string->str;
}

s8 s8_from(usize len, const char *src, tomato_alloc alloc)
{
    if (src == nullptr || alloc == nullptr)
        return;
    s8 out = s8_init(len, alloc);
    if (out == nullptr)
        return nullptr;
    const void *next_null_terminator = memchr(src, '\0', len);
    const usize cpy_len = (next_null_terminator == nullptr) ? len : (char *)next_null_terminator - src;
    memcpy(out, src, cpy_len);
    out[cpy_len] = '\0';
    return out;
}

s8 s8_clone(s8 str, tomato_alloc alloc)
{
    if (str == nullptr)
        return nullptr;
    return s8_from(s8_capacity(str), str, alloc);
}

void s8_free(s8 str, tomato_free free)
{
    if (str == nullptr)
        return;
    memset(get_internal(str), 0, sizeof(internal_s8) + s8_capacity(str));
    if (free != nullptr)
        free(get_internal(str));
}

usize s8_capacity(s8 str)
{
    if (str == nullptr)
        return 0;
    return get_internal(str)->len;
}

i32 s8_cmp(s8 str1, s8 str2)
{
    if (str1 == nullptr || str2 == nullptr)
        return 0;
    const usize     size1 = s8_capacity(str1);
    const usize     size2 = s8_capacity(str2);
    const ptrdiff_t size_diff = size1 - size2;
    if (size_diff == 0)
    {
        return memcmp(str1, str2, s8_capacity(str1));
    }
    const i32 shared_length_cmp = memcmp(str1, str2, (size_diff > 0) ? size2 : size1);
    if (shared_length_cmp != 0)
        return shared_length_cmp;
    return size_diff;
}

b32 s8_eq(s8 str1, s8 str2)
{
    if (str1 == nullptr || str2 == nullptr)
        return false;
    if (s8_capacity(str1) != s8_capacity(str2))
        return false;
    return memcmp(str1, str2, s8_capacity(str1)) == 0;
}

void s8_fill(s8 str, u8 val)
{
    if (str == nullptr)
        return;
    memset(str, val, s8_capacity(str));
}

i32 s8_print(s8 str)
{
    if (str == nullptr)
        return 0;
    return printf("%.*s", (i32)s8_capacity(str), str);
}

i32 s8_debug_print(FILE *file, s8 str)
{
    if (str == nullptr || file == nullptr)
        return 0;
    i32 printed_chars = 0;
    printed_chars += printf("s8(len=%zu, str=\"", s8_capacity(str));
    for (usize i = 0; i < s8_capacity(str); i++)
    {
        fprintf(file, "%2X", str[i] & 0xFF);
    }
    printed_chars += printf("\")");
    return printed_chars + 2 * (i32)s8_capacity(str);
}

/*
// Add view
typedef struct
{
    const s8    start;
    const usize len;
} s8_view;
*/

/*
// Add rope?

static s8       s8slice(u8 *, u8 *);
static bool     s8equals(s8, s8);
static int      s8compare(s8, s8);
static u64      s8hash(s8);
static s8       s8trim(s8);
// static s8       s8clone(s8, arena *);
*/
