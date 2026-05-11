#pragma once

#include <stdio.h>

#include "tomato_allocator.h"
#include "tomato_defines.h"

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
s8 s8_init(usize len, TomatoAllocCtx *ctx);

/* Initializes and returns string with given capacity, populated with src, using provided allocator.
 * len should not include the null terminator.
 */
s8 s8_from(usize len, const char *src, TomatoAllocCtx *ctx);

/* Initializes and returns new string as exact copy of given string using provided allocator. */
s8 s8_clone(s8 str, TomatoAllocCtx *ctx);

/* Frees and zeroes out memory from string using provided free function.
 * If nullptr is passed, only zeroes memory.
 */
void s8_free(s8 str, TomatoAllocCtx *ctx);

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

/* Prints a debug representation of the string in hex to provided file,
 * returns the number of characters printed.
 */
i32 s8_debug_print(FILE *file, s8 str);

// TODO: replace with format specifier macro
/* Prints a debug representation of the string in hex to provided file,
 * returns the number of characters printed.
 */
s8 s8_debug_sprint(s8 str, TomatoAllocCtx *ctx);

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
