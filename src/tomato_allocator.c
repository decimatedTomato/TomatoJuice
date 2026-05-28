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

tomato_alloc_ctx   tomato_libc_malloc_ctx = {wrapped_malloc, wrapped_free, nullptr};
tomato_realloc_ctx tomato_libc_realloc_ctx = {wrapped_realloc, wrapped_free, nullptr};
