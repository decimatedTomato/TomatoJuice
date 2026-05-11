/* Data pointer with size, does not own its memory. */
#define SPAN_INSTANTIATE(ELEMENT_TYPE, TYPENAME)                                                                       \
    typedef struct                                                                                                     \
    {                                                                                                                  \
        const ELEMENT_TYPE *const data;                                                                                \
        const usize               size;                                                                                \
    } span_##TYPENAME;
