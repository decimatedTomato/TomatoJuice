#pragma once

#include "tomato_defines.h"

typedef void *(*tomato_alloc)(usize size, void *allocator_internals);
typedef void *(*tomato_realloc)(void *buffer, usize size, void *allocator_internals);
typedef void (*tomato_free)(void *buffer, void *allocator_internals);

typedef struct
{
    tomato_alloc alloc;
    tomato_free  free;
    void        *allocator_internals;
} tomato_alloc_ctx;

typedef struct
{
    tomato_realloc realloc;
    tomato_free    free;
    void          *allocator_internals;
} tomato_realloc_ctx;

extern tomato_alloc_ctx   tomato_libc_malloc_ctx;
extern tomato_realloc_ctx tomato_libc_realloc_ctx;
