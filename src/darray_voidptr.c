#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    size_t element_size;
    size_t size;
    size_t capacity;
    void *buffer[0];
} vector;

vector *vector_new(size_t capacity, size_t element_size)
{
    vector *ret = malloc(element_size * capacity);
    ret->element_size = element_size;
    ret->size = 0;
    ret->capacity = capacity;
    return ret;
}

void vector_append(vector *vec, void *val)
{
    if (vec->size >= vec->capacity)
        assert(false && "Out of capacity.");
    memcpy(vec->buffer + vec->size++ * vec->element_size, val, vec->element_size);
}

void vector_get(vector *vec, int idx, void *res)
{
    if (vec->size <= 0) assert(false && "Empty.");
    memcpy(res, vec->buffer+vec->element_size * idx, vec->element_size);
}

int main()
{
    vector *vec = vector_new(10, sizeof(int));
    int val = 42;
    vector_append(vec, &val);
    int res = 0;
    vector_get(vec, 0, &res);
    printf("%i", res);
}