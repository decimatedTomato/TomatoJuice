#include "tomato_dynarray.h"

struct Person
{
    const char *name;
    i32         year_of_birth;
    double      height;
};

TOMATO_DYNARRAY_INSTANTIATE(i32, i)
TOMATO_DYNARRAY_INSTANTIATE(struct Person, person)

int main()
{
    tomato_dynarray_i da = {0};
    tomato_dynarray_append_i(&da, 1);
    tomato_dynarray_option_i opt = tomato_dynarray_get_i(&da, 10);
    (void)opt;
}
