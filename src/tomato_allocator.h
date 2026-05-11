#pragma once

#include "tomato_defines.h"

typedef struct TomatoAllocatorContext TomatoAllocCtx;

typedef void *(*tomato_alloc)(usize size, void *allocator_internals);
typedef void (*tomato_free)(void *buffer, void *allocator_internals);

struct TomatoAllocatorContext
{
    tomato_alloc alloc;
    tomato_free  free;
    void        *allocator_internals;
};

extern TomatoAllocCtx libc_malloc_ctx;
