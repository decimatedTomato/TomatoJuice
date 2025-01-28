#pragma once

#include "tomato_defines.h"

#include <stdio.h>
#include <string.h>
/* FIXME all functions which edit strings keep a null terminator (for compatibility with string.h) */
/* FIXME add comments explaining interface */
/* What testing framework should I use? Or should I wrote my own one? */
/* Should I add const to everything I can? */
/* Should I make functions that manage memory take in allocators/deallocators or use a global memory management strategy
 * like so: ?*/
#ifndef TOMATO_STRING_ALLOC
#include <stdlib.h>
#define TOMATO_STRING_ALLOC(X) calloc(X, sizeof(char))
#define TOMATO_STRING_FREE free
#endif

// String type that owns its memory, sane interface available below
typedef char *s8;

// TODO: Can this macro be used inline?
// TODO make macro prevent pointers from being passed
/* Initializes s8 string the size of src and then copies contents from src
 * Note: Use macro only in scope that string was declared in
 */
#define S8(c_str) s8_from(lengthof(c_str), (c_str))

/* Initializes memory for s8 string */
s8 s8_init(usize len);

/* Frees and zeroes out memory from s8 string */
void s8_free(s8 str);

s8 s8_from(usize len, const char *src);

usize s8_len(s8 str);

i32 s8_cmp(s8 str1, s8 str2);

b32 s8_eq(s8 str1, s8 str2);

s8 s8_concat(s8 str1, s8 str2);

s8 s8_clone(s8 str);

void s8_fill(s8 str, u8 data);

i32 s8_print(s8 str);

i32 s8_debug_print(s8 str);

typedef struct
{
    usize len;
    char  str[];
} internal_s8;

s8 s8_init(usize len)
{
    internal_s8 *string = (internal_s8 *)TOMATO_STRING_ALLOC(sizeof(internal_s8) + len + 1);
    string->len = len;
    return string->str;
}

void s8_free(s8 str)
{
    memset((internal_s8 *)(str)-1, 0, sizeof(internal_s8) + s8_len(str));
    TOMATO_STRING_FREE((internal_s8 *)(str)-1);
}

s8 s8_from(usize len, const char *src)
{
    s8 out = s8_init(len);
    memcpy(out, src, len);
    return out;
}

usize s8_len(s8 str)
{
    return (((internal_s8 *)(str)) - 1)->len;
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
    printed_chars += printf("s8(len=%zu, str=\"", s8_len(str));
    for (usize i = 0; i < s8_len(str); i++)
    {
        printf("%2X", str[i] & 0xFF);
    }
    printed_chars += printf("\")");
    return printed_chars + 2 * (i32)s8_len(str);
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
