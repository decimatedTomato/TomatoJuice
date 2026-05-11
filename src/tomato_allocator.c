#include "tomato_allocator.h"

#include <stdlib.h>

void *wrapped_malloc(usize sz, void *)
{
    return malloc(sz);
}
void wrapped_free(void *buffer, void *)
{
    free(buffer);
}

TomatoAllocCtx libc_malloc_ctx = {wrapped_malloc, wrapped_free, nullptr};
