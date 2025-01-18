# TomatoJuice

**My reusable c code library**

## Contains:
- Custom string type

## TODO SHORTTERM:
- More convenient string (owning)
    - Compatible with libc's "string.h"
    - More efficient operations
    - Take a string_view of it (non-owning)
- write unit tests for string library
- write tests using a fuzzer

## NEXT STEPS
- Figure out how to debug while testing in vscode
- Is there a test you can write that checks for things like memory leaks or how much memory an allocation reserves or can you test whether memory is uninitialized?
- What are the mocks from googletest used for, sounds like more of a c++ thing, or can I for example provide a mock malloc to test allocations?



## TODO LONGTERM:
- Sane string
- Data structures
    - string rope
    - resizable array
    - hashtable
- Serialization
- Tokenizer/Parser
- Math
- Physics
- Rendering
- Convenience utilities
- Memory allocators