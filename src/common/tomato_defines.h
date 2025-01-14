#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <uchar.h>

typedef uint8_t   u8;
typedef char16_t  c16;
typedef int32_t   b32;
typedef int32_t   i32;
typedef uint32_t  u32;
typedef uint64_t  u64;
typedef float     f32;
typedef double    f64;
typedef uintptr_t uptr;
typedef char      byte;
// typedef ptrdiff_t size;
typedef size_t usize;

// #define sizeof(x)    (size)sizeof(x)
// #define alignof(x)   (size)_Alignof(x)
#define countof(a) (sizeof(a) / sizeof((a)[0]))
#define lengthof(s) (countof(s) - 1)

/*   #define assert(c) \
     while (!(c)) \
     __builtin_unreachable()
*/