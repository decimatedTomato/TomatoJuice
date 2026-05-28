// https://nullprogram.com/blog/2023/09/27/

#include "tomato_allocator.h"
#include "tomato_defines.h"

#define TOMATO_ARENA_DEFAULT_CAPACITY 8 * 1024 * 1024
#define TOMATO_ARENA_NEW tomato_arena_new(TOMATO_ARENA_DEFAULT_CAPACITY)
#define TOMATO_ARENA_ALLOC(TOMATO_ARENA, TYPE) tomato_arena_aligned_alloc(&TOMATO_ARENA, sizeof(TYPE), alignof(TYPE))
#define TOMATO_ARENA_ALLOC_CTX(TOMATO_ARENA)                                                                           \
    (tomato_alloc_ctx)                                                                                                 \
    {                                                                                                                  \
        tomato_arena_alloc, tomato_free_noop, TOMATO_ARENA                                                             \
    }
#define TOMATO_ARENA_ALIGNED_ALLOC_CTX(TOMATO_ARENA)                                                                   \
    (tomato_aligned_alloc_ctx)                                                                                         \
    {                                                                                                                  \
        tomato_arena_aligned_alloc, tomato_free_noop, TOMATO_ARENA                                                     \
    }
#define TOMATO_ARENA_MONOTONIC_ALLOC_CTX(TOMATO_ARENA)                                                                 \
    (tomato_monotonic_alloc_ctx)                                                                                       \
    {                                                                                                                  \
        tomato_arena_aligned_alloc, TOMATO_ARENA                                                                       \
    }

typedef struct
{
    byte *buffer;
    byte *cursor;
    usize capacity;
} tomato_arena;

b32          tomato_arena_init(tomato_arena *arena, usize capacity);
tomato_arena tomato_arena_new(usize capacity);
void        *tomato_arena_aligned_alloc(tomato_arena *arena, usize size, usize alignment);
void        *tomato_arena_alloc(tomato_arena *arena, usize size);
void         tomato_arena_clear(tomato_arena *arena);
usize        tomato_arena_remaining_bytes(tomato_arena *arena);
void         tomato_arena_free(tomato_arena *arena);

extern tomato_alloc_ctx tomato_arena_alloc_ctx;
