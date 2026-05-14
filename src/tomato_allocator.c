#include "tomato_allocator.h"

#include <stdlib.h>

void *wrapped_malloc(usize size, void *)
{
    return malloc(size);
}
void *wrapped_realloc(void *buffer, usize size, void *)
{
    return realloc(buffer, size);
}
void wrapped_free(void *buffer, void *)
{
    free(buffer);
}

TomatoAllocCtx   libc_malloc_ctx = {wrapped_malloc, wrapped_free, nullptr};
TomatoReallocCtx libc_realloc_ctx = {wrapped_realloc, wrapped_free, nullptr};
