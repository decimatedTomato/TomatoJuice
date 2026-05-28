#include "tomato_string.h"

#include <string.h>

#include "tomato_allocator.h"

typedef struct
{
    usize len;
    char  str[];
} internal_s8;

static internal_s8 *get_internal(s8 str)
{
    return ((internal_s8 *)str) - 1;
}

s8 s8_init(usize len, tomato_alloc_ctx *ctx)
{
    if (ctx == nullptr)
        return nullptr;
    internal_s8 *string = (internal_s8 *)ctx->alloc(sizeof(internal_s8) + len + 1, ctx->allocator_internals);
    if (string == nullptr)
        return nullptr;
    string->len = len;
    string->str[0] = '\0';
    return string->str;
}

s8 s8_from(usize len, const char *src, tomato_alloc_ctx *ctx)
{
    if (src == nullptr || ctx == nullptr)
        return nullptr;
    s8 out = s8_init(len, ctx);
    if (out == nullptr)
        return nullptr;
    const void *next_null_terminator = memchr(src, '\0', len);
    const usize cpy_len = (next_null_terminator == nullptr) ? len : (char *)next_null_terminator - src;
    memcpy(out, src, cpy_len);
    out[cpy_len] = '\0';
    return out;
}

s8 s8_clone(s8 str, tomato_alloc_ctx *ctx)
{
    if (str == nullptr || ctx == nullptr)
        return nullptr;
    return s8_from(s8_capacity(str), str, ctx);
}

void s8_free(s8 str, tomato_alloc_ctx *ctx)
{
    if (str == nullptr)
        return;
    // TODO: Test this behavior
    memset(get_internal(str), 0, sizeof(internal_s8) + s8_capacity(str));
    if (ctx != nullptr)
        ctx->free(get_internal(str), ctx->allocator_internals);
}

usize s8_capacity(s8 str)
{
    if (str == nullptr)
        return 0;
    return get_internal(str)->len;
}

i32 s8_cmp(s8 str1, s8 str2)
{
    if (str1 == nullptr || str2 == nullptr)
        return 0;
    const usize     size1 = s8_capacity(str1);
    const usize     size2 = s8_capacity(str2);
    const ptrdiff_t size_diff = size1 - size2;
    if (size_diff == 0)
    {
        return memcmp(str1, str2, s8_capacity(str1));
    }
    const i32 shared_length_cmp = memcmp(str1, str2, (size_diff > 0) ? size2 : size1);
    if (shared_length_cmp != 0)
        return shared_length_cmp;
    return size_diff;
}

b32 s8_eq(s8 str1, s8 str2)
{
    if (str1 == nullptr || str2 == nullptr)
        return false;
    if (s8_capacity(str1) != s8_capacity(str2))
        return false;
    return memcmp(str1, str2, s8_capacity(str1)) == 0;
}

void s8_fill(s8 str, u8 val)
{
    if (str == nullptr)
        return;
    memset(str, val, s8_capacity(str));
}

i32 s8_debug_print(FILE *file, s8 str)
{
    if (str == nullptr || file == nullptr)
        return 0;
    i32 printed_chars = 0;
    printed_chars += printf("s8(len=%zu, str=\"", s8_capacity(str));
    for (usize i = 0; i < s8_capacity(str); i++)
    {
        fprintf(file, "%2X", str[i] & 0xFF);
    }
    printed_chars += printf("\")");
    return printed_chars + 2 * (i32)s8_capacity(str);
}
