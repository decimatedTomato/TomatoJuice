#pragma once

#include "defines.h"

/* FIXME all functions which edit strings keep a null terminator (for compatibility with string.h) */
/* FIXME add comments explaining interface */
/* Should I add const to everything I can? */
/* Should I make functions that manage memory take in allocators/deallocators or use a global memory management strategy
 * like so: ?*/
#ifndef TOMATO_STRING_ALLOC
void free(void *);
#define TOMATO_STRING_FREE free
void *calloc(size_t, size_t);
#define TOMATO_STRING_ALLOC(X) calloc(X, sizeof(u8))
#endif

// Treats strings as arrays of unsigned bytes
typedef u8 *s8;
// Uses a private owning struct
typedef struct
{
    usize len;
    u8    str[];
} s8_owning;

// TODO: Can this macro be used inline?
/* Note: Use macro only in scope that string was declared in */
#define S8(c_str) s8_from(lengthof(c_str), (c_str))

/* Initializes memory for s8 string */
s8 s8_init(usize len);

void s8_free(s8 str);

/* Initializes s8 string the size of src and then copies contents from src */
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
    const s8    start;
    const usize len;
} s8_view;

/*
// Add rope?

static s8       s8slice(u8 *, u8 *);
static bool     s8equals(s8, s8);
static int      s8compare(s8, s8);
static u64      s8hash(s8);
static s8       s8trim(s8);
// static s8       s8clone(s8, arena *);
*/
