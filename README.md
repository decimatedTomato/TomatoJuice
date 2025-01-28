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

## HOW TO USE:
- Release build has not been configured yet!
- If using vscode for debugger interface:
    - To debug tests on windows open "x64 Native Tools Command Prompt for VS 2022", from there open vscode
    - For linux on WSL2 Ubuntu 22.04.5 LTS I could not get the vscode debugger working
    - >&"warning: GDB: Failed to set controlling terminal: Operation not permitted\n"
    [1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-bx1bxyjj.nva" 1>"/tmp/Microsoft-MIEngine-Out-1lsxywui.jr1"

    - Link trying to solve this: https://github.com/microsoft/WSL/issues/8356
    - I tried downloading an older gdb that supposedly doesn't cause the problem but couldn't build it (>//<)
    - For now I will use gdb in the command line or through the gf frontend https://github.com/nakst/gf