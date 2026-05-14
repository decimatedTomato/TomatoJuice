# TomatoJuice

**My reusable c code library**

## CONTAINS:
- Memory allocator concept
- Sane strings
- Resizable vectors

## HOW TO USE:
Import one of the libraries into your project and include the associated header.

## REQUIREMENTS:
- C compiler with C23 support.

## SUPPORTED PLATFORMS
- Windows with MSVC
- Linux with gcc

## TODO SHORTTERM:
- Improve interface of generic dynamic arrays
    - tests
    - make allocator aware?
- Strings
    - Improve printing functionality with format specifier macro
    - Stringbuf (owning)
        - tests
    - string_view of it (non-owning)
        - write unit tests for string library

## QUESTION
- Shouldn't the memory-aware types store a pointer to the allocator context so they know how to free themselves?

## TODO LONGTERM:
- Data structures
    - string rope
    - hashtable
- Custom assert that triggers in all build types and includes formatted text and
    - Logging could also fit in here
- Serialization
- Tokenizer/Parser
- Math
- Physics
- Rendering
- Convenience utilities
- Replace clang-format with clang-tidy
- Add support for mingw
- Add support for clang on linux
- Add support for clang-cl on windows
- Give options to build as static libraries or dynamic ones
- Make address sanitizers optional in tests
- write tests using a fuzzer
    - how?
- Can fixtures be used to make tests more efficient?

## HOW TO TEST:
- On windows:
    - Build `build_test.bat`
    - Run `test\build\Debug\test_tomato_juice.exe`
- In order to use a visual debugger on windows:
    - Open "x64 Native Tools Command Prompt for VS 2022"
    - From that terminal, start the debugger
    - Run `test\build\Debug\test_tomato_juice.exe --gtest_break_on_failure`
- On linux
    - Build `./build_test.sh`
    - Run `./test/build/test_tomato_juice`
- In order to use a visual debugger on linux:
    - I had some trouble (¬_¬ )
    - For linux on WSL2 Ubuntu 22.04.5 LTS I could not get the vscode debugger working
    - >&"warning: GDB: Failed to set controlling terminal: Operation not permitted\n"
    [1] + Done                       "/usr/bin/gdb" --interpreter=mi --tty=${DbgTerm} 0<"/tmp/Microsoft-MIEngine-In-bx1bxyjj.nva" 1>"/tmp/Microsoft-MIEngine-Out-1lsxywui.jr1"
    - Link trying to solve this: https://github.com/microsoft/WSL/issues/8356
    - I am able to use gdb in the command line or through the gf frontend https://github.com/nakst/gf