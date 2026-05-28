#include <stdio.h>

#include "tomato_defines.h"
#include "tomato_dynarray.h"

TOMATO_DYNARRAY_INSTANTIATE(i32, int32_t)

void print_i32(i32 *val)
{
    printf("%i, ", *val);
}

b32 test_da_append_size_increases()
{
    b32                     ret = false;
    const i32               array_size = 10;
    tomato_dynarray_int32_t da = {0};
    for (i32 i = 0; i < array_size; i++)
        tomato_dynarray_int32_t_append(&da, i);
    if (da.buffer == nullptr)
        ret = true;
    ;
    if (da.size != array_size)
        ret = true;
    ;
    if (da.capacity < array_size)
        ret = true;
    ;
    tomato_dynarray_int32_t_free(&da);
    return ret;
}
b32 test_da_get_fails()
{
    b32                     ret = false;
    const i32               array_size = 10;
    tomato_dynarray_int32_t da = {0};
    for (i32 i = 0; i < array_size; i++)
        tomato_dynarray_int32_t_append(&da, i);
    tomato_dynarray_int32_t_option opt = tomato_dynarray_int32_t_get(&da, array_size);
    if (opt.has_value)
        ret = true;
    if (opt.value != 0)
        ret = true;
    tomato_dynarray_int32_t_free(&da);
    return ret;
}
b32 test_da_get_succeeds()
{
    b32                     ret = false;
    const i32               array_size = 10;
    tomato_dynarray_int32_t da = {0};
    for (i32 i = 0; i < array_size; i++)
        tomato_dynarray_int32_t_append(&da, i);
    tomato_dynarray_int32_t_option opt = tomato_dynarray_int32_t_get(&da, array_size - 1);
    if (!opt.has_value)
        ret = true;
    if (opt.value != array_size - 1)
        ret = true;
    tomato_dynarray_int32_t_free(&da);
    return ret;
}
b32 test_da_pop_fails()
{
    b32                     ret = false;
    const i32               array_size = 10;
    tomato_dynarray_int32_t da = {0};
    for (i32 i = 0; i < array_size; i++)
        tomato_dynarray_int32_t_append(&da, i);
    tomato_dynarray_int32_t_option opt = tomato_dynarray_int32_t_pop(&da, array_size - 1);
    if (!opt.has_value)
        ret = true;
    if (opt.value != array_size - 1)
        ret = true;
    tomato_dynarray_int32_t_free(&da);
    return ret;
}
b32 test_da_pop_succeeds()
{
    b32                     ret = false;
    const i32               array_size = 10;
    tomato_dynarray_int32_t da = {0};
    for (i32 i = 0; i < array_size; i++)
        tomato_dynarray_int32_t_append(&da, i);
    tomato_dynarray_int32_t_option opt = tomato_dynarray_int32_t_pop(&da, -2);
    if (opt.has_value)
        ret = true;
    if (opt.value != 0)
        ret = true;
    tomato_dynarray_int32_t_free(&da);
    return ret;
}
b32 test_da_shrink_fails()
{
    b32                     ret = false;
    const i32               array_size = 10;
    tomato_dynarray_int32_t da = {0};
    for (i32 i = 0; i < array_size; i++)
        tomato_dynarray_int32_t_append(&da, i);
    if (!tomato_dynarray_int32_t_shrink(&da, ((i32)da.size - 1)))
        ret = true;
    tomato_dynarray_int32_t_free(&da);
    return ret;
}
b32 test_da_shrink_succeeds()
{
    b32                     ret = false;
    const i32               array_size = 10;
    tomato_dynarray_int32_t da = {0};
    for (i32 i = 0; i < array_size; i++)
        tomato_dynarray_int32_t_append(&da, i);
    if (tomato_dynarray_int32_t_shrink(&da, da.size))
        ret = true;
    tomato_dynarray_int32_t_free(&da);
    return ret;
}
b32 test_da_insert_fails()
{
    b32                     ret = false;
    const i32               array_size = 10;
    tomato_dynarray_int32_t da = {0};
    for (i32 i = 0; i < array_size; i++)
        tomato_dynarray_int32_t_append(&da, i);
    if (!tomato_dynarray_int32_t_insert(&da, -1, -1))
        ret = true;
    tomato_dynarray_int32_t_free(&da);
    return ret;
}
b32 test_da_insert_succeeds()
{
    b32                     ret = false;
    const i32               array_size = 10;
    tomato_dynarray_int32_t da = {0};
    for (i32 i = 0; i < array_size; i++)
        tomato_dynarray_int32_t_append(&da, i);
    if (tomato_dynarray_int32_t_insert(&da, -1, 0))
        ret = true;
    if (da.buffer[0] != -1)
        ret = true;
    tomato_dynarray_int32_t_free(&da);
    return ret;
}
b32 test_da_foreach()
{
    b32                     ret = false;
    const i32               array_size = 10;
    tomato_dynarray_int32_t da = {0};
    for (i32 i = 0; i < array_size; i++)
        tomato_dynarray_int32_t_append(&da, i);
    tomato_dynarray_int32_t_foreach(&da, print_i32);
    tomato_dynarray_int32_t_free(&da);
    return ret;
}
