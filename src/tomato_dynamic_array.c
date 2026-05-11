#include <assert.h>
#include <stdbool.h>

#define VECTOR_INSTANTIATE(TYPE)                                                                                       \
    typedef struct                                                                                                     \
    {                                                                                                                  \
        size_t size;                                                                                                   \
        size_t capacity;                                                                                               \
        TYPE   buffer[];                                                                                               \
    } vector_##TYPE;                                                                                                   \
    vector_##TYPE *vector_new_##TYPE(size_t capacity)                                                                  \
    {                                                                                                                  \
        vector_##TYPE *ret = malloc(sizeof(TYPE) * capacity);                                                          \
        ret->size = 0;                                                                                                 \
        ret->capacity = capacity;                                                                                      \
        return ret;                                                                                                    \
    }                                                                                                                  \
    TYPE vector_get_##TYPE(vector_##TYPE *vec, int idx)                                                                \
    {                                                                                                                  \
        if (vec->size <= 0)                                                                                            \
            assert(false && "Out of capacity.");                                                                       \
        return vec->buffer[idx];                                                                                       \
    }                                                                                                                  \
    void vector_append_##TYPE(vector_##TYPE *vec, TYPE val)                                                            \
    {                                                                                                                  \
        if (vec->size >= vec->capacity)                                                                                \
            assert(false && "Empty.");                                                                                 \
        vec->buffer[vec->size++] = val;                                                                                \
    }
