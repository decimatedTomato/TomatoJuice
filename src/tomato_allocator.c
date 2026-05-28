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
void *wrapped_aligned_alloc(usize size, usize alignment, void *)
{
#if defined(_WIN32)
    return _aligned_malloc(size, alignment);
#elif defined(__unix__)
    return aligned_alloc(alignment, size);
#endif
}
void wrapped_aligned_free(void *buffer, void *)
{
#if defined(_WIN32)
    _aligned_free(buffer);
#elif defined(__unix__)
    free(buffer);
#endif
}

void tomato_free_noop(void *, void *)
{
}

tomato_alloc_ctx         tomato_libc_malloc_ctx = {wrapped_malloc, wrapped_free, nullptr};
tomato_realloc_ctx       tomato_libc_realloc_ctx = {wrapped_realloc, wrapped_free, nullptr};
tomato_aligned_alloc_ctx tomato_libc_aligned_alloc_ctx = {wrapped_aligned_alloc, wrapped_aligned_free, nullptr};
