// #pragma once

void         *memmove(void *dest, const void *src, size_t count);
long long int llround(double x);
#define max(a, b) (((a) > (b)) ? (a) : (b))

#include "tomato_assert.h"  // IWYU pragma: keep
#include "tomato_defines.h" // IWYU pragma: keep

/**
 * Resizable array for primative types.
 *
 * Uses an array which can be accessed like normal.
 * Size and capacity can also be read.
 * Supports appending, safe access, safe popping, inserting, foreach and resizing.
 *
 * Example usage:
 * TOMATO_DYNARRAY_INSTANTIATE(int, i)
 *
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
        bool has_value;                                                                                                \
        TYPE value;                                                                                                    \
    } tomato_dynarray_option_##SUFFIX;                                                                                 \
    typedef struct                                                                                                     \
    {                                                                                                                  \
        TYPE *buffer;                                                                                                  \
        usize size;                                                                                                    \
        usize capacity;                                                                                                \
    } tomato_dynarray_##SUFFIX;                                                                                        \
    bool tomato_dynarray_reserve_##SUFFIX(tomato_dynarray_##SUFFIX *da, usize new_capacity)                            \
    {                                                                                                                  \
        if (new_capacity <= da->capacity)                                                                              \
            return false;                                                                                              \
        TYPE *buffer = TOMATO_CAST(TYPE *) realloc(da->buffer, new_capacity);                                          \
        if (buffer == nullptr)                                                                                         \
            return true;                                                                                               \
        da->buffer = buffer;                                                                                           \
        da->capacity = new_capacity;                                                                                   \
        return false;                                                                                                  \
    }                                                                                                                  \
    void tomato_dynarray_grow_##SUFFIX(tomato_dynarray_##SUFFIX *da)                                                   \
    {                                                                                                                  \
        if (da->size == da->capacity)                                                                                  \
            TOMATO_ASSERT(                                                                                             \
                !tomato_dynarray_reserve_##SUFFIX(                                                                     \
                    da, max(TOMATO_MIN_ARRAY_LEN, (usize)llround(TOMATO_GROWTH_FACTOR * da->capacity))) &&             \
                "Append failed due to a failed memory reservation");                                                   \
    }                                                                                                                  \
    bool tomato_dynarray_shrink_##SUFFIX(tomato_dynarray_##SUFFIX *da, usize new_capacity)                             \
    {                                                                                                                  \
        if (new_capacity > da->capacity || new_capacity > da->size)                                                    \
            return true;                                                                                               \
        TYPE *buffer = TOMATO_CAST(TYPE *) realloc(da->buffer, new_capacity);                                          \
        if (buffer == nullptr)                                                                                         \
            return true;                                                                                               \
        da->buffer = buffer;                                                                                           \
        da->capacity = new_capacity;                                                                                   \
        return false;                                                                                                  \
    }                                                                                                                  \
    void tomato_dynarray_append_##SUFFIX(tomato_dynarray_##SUFFIX *da, TYPE val)                                       \
    {                                                                                                                  \
        tomato_dynarray_grow_##SUFFIX(da);                                                                             \
        da->buffer[da->size++] = val;                                                                                  \
    }                                                                                                                  \
    tomato_dynarray_option_##SUFFIX tomato_dynarray_get_##SUFFIX(tomato_dynarray_##SUFFIX *da, i32 idx)                \
    {                                                                                                                  \
        if (idx < 0 || (usize)idx > da->size)                                                                          \
            return TOMATO_C_LITERAL(tomato_dynarray_option_##SUFFIX){.has_value = false, .value = {}};                 \
        return TOMATO_C_LITERAL(tomato_dynarray_option_##SUFFIX){.has_value = true, .value = da->buffer[idx]};         \
    }                                                                                                                  \
    tomato_dynarray_option_##SUFFIX tomato_dynarray_pop_##SUFFIX(tomato_dynarray_##SUFFIX *da, i32 idx)                \
    {                                                                                                                  \
        if (idx < 0 || (usize)idx > da->size)                                                                          \
            return TOMATO_C_LITERAL(tomato_dynarray_option_##SUFFIX){.has_value = false, .value = {}};                 \
        tomato_dynarray_option_##SUFFIX ret = {.has_value = true, .value = da->buffer[idx]};                           \
        memmove(&da->buffer[idx], &da->buffer[idx + 1], --(da->size) - idx);                                           \
        return ret;                                                                                                    \
    }                                                                                                                  \
    bool tomato_dynarray_insert_##SUFFIX(tomato_dynarray_##SUFFIX *da, TYPE val, i32 idx)                              \
    {                                                                                                                  \
        if (idx < 0 || (usize)idx > da->size)                                                                          \
            return true;                                                                                               \
        tomato_dynarray_grow_##SUFFIX(da);                                                                             \
        memmove(&da->buffer[idx + 1], &da->buffer[idx], (da->size)++ - idx);                                           \
        da->buffer[idx] = val;                                                                                         \
        return false;                                                                                                  \
    }                                                                                                                  \
    void tomato_dynarray_foreach_##SUFFIX(tomato_dynarray_##SUFFIX *da, void (*func)(TYPE *))                          \
    {                                                                                                                  \
        for (usize i = 0; i < da->size; i++)                                                                           \
            func(&da->buffer[i]);                                                                                      \
    }                                                                                                                  \
    void tomato_dynarray_free_##SUFFIX(tomato_dynarray_##SUFFIX *da)                                                   \
    {                                                                                                                  \
        free(da->buffer);                                                                                              \
        da->buffer = nullptr;                                                                                          \
        da->size = 0;                                                                                                  \
        da->capacity = 0;                                                                                              \
    }
