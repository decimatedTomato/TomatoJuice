#pragma once

#include <math.h>

#include "tomato_assert.h"  // IWYU pragma: keep
#include "tomato_defines.h" // IWYU pragma: keep

void *memmove(void *dest, const void *src, usize count);
#define max(a, b) (((a) > (b)) ? (a) : (b))

/**
 * Resizable array for primative types.
 *
 * Uses an array which can be accessed like normal.
 * Size and capacity can also be read.
 * Supports appending, safe access, safe popping, inserting, foreach and resizing.
 *
 * Tradeoffs of monomorphization (instantiating template with different types).
 * (+) Functions are more typesafe because they know their types at compile-time.
 * (+) Compiler might make specialized optimizations for each type.
 * (+) This leads to lsp support.
 * (-) Identical code is duplicated across instantiations.
 * (-) Functions are part of macros making for painful debugging experience as source location is useless.
 * (-) Development is a pain since clangd only reevaluates macros on restart.
 * Other possible implementations include:
 * - Type-erased generics (using sizeof to account for different element types).
 * (+) Adding new types that fulfill the contract of the functions is dead easy and can have semantically significant
 * names.
 * (+) More functions can easily be added which make use of the interface or act on specific implementations of the
 * interface.
 * (+) Less code duplication.
 * (-) Contract that type must fulfill is not checked at compile time leading to mistakes.
 * (-) Type not being known within function call makes it harder to debug.
 * - Void pointer generics (using indirection and casting at callsite for different element types).
 * (-) Extra layer of indirection adds complexity (where to store allocation) and isn't performant.
 *
 * Example usage:
 * #include "tomato_dynarray.h"
 * TOMATO_DYNARRAY_INSTANTIATE(int, i)
 * int main()
 * {
 *     tomato_dynarray_i da = {0};
 *     tomato_dynarray_i_
 * }
 */

#define TOMATO_GROWTH_FACTOR 1.5
#define TOMATO_MIN_ARRAY_LEN 4

#ifdef __cplusplus
#define TOMATO_CAST(TYPE) (TYPE)
#define TOMATO_C_LITERAL(TYPE) TYPE
#else
#define TOMATO_CAST(TYPE)
#define TOMATO_C_LITERAL(TYPE) (TYPE)
#endif // __cplusplus

#define TOMATO_DYNARRAY_INSTANTIATE(TYPE, SUFFIX)                                                                      \
    typedef struct                                                                                                     \
    {                                                                                                                  \
        b32  has_value;                                                                                                \
        TYPE value;                                                                                                    \
    } tomato_dynarray_##SUFFIX##_option;                                                                               \
    typedef struct                                                                                                     \
    {                                                                                                                  \
        TYPE *buffer;                                                                                                  \
        usize size;                                                                                                    \
        usize capacity;                                                                                                \
    } tomato_dynarray_##SUFFIX;                                                                                        \
    b32 tomato_dynarray_##SUFFIX##_reserve(tomato_dynarray_##SUFFIX *da, usize new_capacity)                           \
    {                                                                                                                  \
        if (new_capacity <= da->capacity)                                                                              \
            return false;                                                                                              \
        TYPE *buffer = TOMATO_CAST(TYPE *) realloc(da->buffer, sizeof(TYPE) * new_capacity);                           \
        if (buffer == nullptr)                                                                                         \
            return true;                                                                                               \
        da->buffer = buffer;                                                                                           \
        da->capacity = new_capacity;                                                                                   \
        return false;                                                                                                  \
    }                                                                                                                  \
    void tomato_dynarray_##SUFFIX##_grow(tomato_dynarray_##SUFFIX *da)                                                 \
    {                                                                                                                  \
        if (da->size == da->capacity)                                                                                  \
        {                                                                                                              \
            TOMATO_ATTR_UNUSED b32 success = !tomato_dynarray_##SUFFIX##_reserve(                                      \
                da, max(TOMATO_MIN_ARRAY_LEN, (usize)llround(TOMATO_GROWTH_FACTOR * da->capacity)));                   \
            TOMATO_ASSERT(success && "Append failed due to a failed memory reservation");                              \
        }                                                                                                              \
    }                                                                                                                  \
    b32 tomato_dynarray_##SUFFIX##_shrink(tomato_dynarray_##SUFFIX *da, usize new_capacity)                            \
    {                                                                                                                  \
        if (new_capacity > da->capacity || new_capacity < da->size || new_capacity == 0)                               \
            return true;                                                                                               \
        TYPE *buffer = TOMATO_CAST(TYPE *) realloc(da->buffer, sizeof(TYPE) * new_capacity);                           \
        if (buffer == nullptr)                                                                                         \
            return true;                                                                                               \
        da->buffer = buffer;                                                                                           \
        da->capacity = new_capacity;                                                                                   \
        return false;                                                                                                  \
    }                                                                                                                  \
    void tomato_dynarray_##SUFFIX##_append(tomato_dynarray_##SUFFIX *da, TYPE val)                                     \
    {                                                                                                                  \
        tomato_dynarray_##SUFFIX##_grow(da);                                                                           \
        da->buffer[da->size++] = val;                                                                                  \
    }                                                                                                                  \
    tomato_dynarray_##SUFFIX##_option tomato_dynarray_##SUFFIX##_get(tomato_dynarray_##SUFFIX *da, i32 idx)            \
    {                                                                                                                  \
        if (idx < 0 || idx > (i32)da->size - 1)                                                                        \
            return TOMATO_C_LITERAL(tomato_dynarray_##SUFFIX##_option){.has_value = false, .value = {}};               \
        return TOMATO_C_LITERAL(tomato_dynarray_##SUFFIX##_option){.has_value = true, .value = da->buffer[idx]};       \
    }                                                                                                                  \
    tomato_dynarray_##SUFFIX##_option tomato_dynarray_##SUFFIX##_pop(tomato_dynarray_##SUFFIX *da, i32 idx)            \
    {                                                                                                                  \
        if (idx < 0 || (usize)idx > da->size)                                                                          \
            return TOMATO_C_LITERAL(tomato_dynarray_##SUFFIX##_option){.has_value = false, .value = {}};               \
        tomato_dynarray_##SUFFIX##_option ret = {.has_value = true, .value = da->buffer[idx]};                         \
        memmove(&da->buffer[idx], &da->buffer[idx + 1], sizeof(TYPE) * (--(da->size) - idx));                          \
        return ret;                                                                                                    \
    }                                                                                                                  \
    b32 tomato_dynarray_##SUFFIX##_insert(tomato_dynarray_##SUFFIX *da, TYPE val, i32 idx)                             \
    {                                                                                                                  \
        if (idx < 0 || (usize)idx > da->size)                                                                          \
            return true;                                                                                               \
        tomato_dynarray_##SUFFIX##_grow(da);                                                                           \
        memmove(&da->buffer[idx + 1], &da->buffer[idx], sizeof(TYPE) * ((da->size)++ - idx));                          \
        da->buffer[idx] = val;                                                                                         \
        return false;                                                                                                  \
    }                                                                                                                  \
    void tomato_dynarray_##SUFFIX##_foreach(tomato_dynarray_##SUFFIX *da, void (*func)(TYPE *))                        \
    {                                                                                                                  \
        for (usize i = 0; i < da->size; i++)                                                                           \
            func(&da->buffer[i]);                                                                                      \
    }                                                                                                                  \
    void tomato_dynarray_##SUFFIX##_free(tomato_dynarray_##SUFFIX *da)                                                 \
    {                                                                                                                  \
        free(da->buffer);                                                                                              \
        da->buffer = nullptr;                                                                                          \
        da->size = 0;                                                                                                  \
        da->capacity = 0;                                                                                              \
    }
