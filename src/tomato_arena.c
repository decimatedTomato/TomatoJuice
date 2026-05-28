#include "tomato_arena.h"

b32 tomato_arena_init(tomato_arena *arena, usize capacity)
{
    arena->buffer = malloc(capacity);
    if (arena->buffer == nullptr)
        return true;
    arena->cursor = arena->buffer;
    arena->capacity = capacity;
    return false;
}
tomato_arena tomato_arena_new(usize capacity)
{
    byte *buffer = malloc(capacity);
    return (tomato_arena){buffer, buffer, capacity};
}
void *tomato_arena_aligned_alloc(tomato_arena *arena, usize size, usize alignment)
{
    // align cursor to alignment boundary
    uptr allocation = (uptr)arena->cursor + (uptr)arena->cursor % alignment;
    // check if there is enough room for allocation
    if (allocation + size > (uptr)arena->buffer + arena->capacity)
    {
        return nullptr;
    }
    // adjust cursor to byte after allocation
    arena->cursor = (char *)(allocation + size);
    return (void *)allocation;
}
void *tomato_arena_alloc(tomato_arena *arena, usize size)
{
    return tomato_arena_aligned_alloc(arena, size, size);
}
void tomato_arena_clear(tomato_arena *arena)
{
    arena->cursor = arena->buffer;
}
usize tomato_arena_remaining_bytes(tomato_arena *arena)
{
    return arena->capacity - ((uptr)arena->cursor - (uptr)arena->buffer);
}
void tomato_arena_free(tomato_arena *arena)
{
    free(arena->buffer);
    arena->buffer = nullptr;
    arena->cursor = nullptr;
    arena->capacity = 0;
}
