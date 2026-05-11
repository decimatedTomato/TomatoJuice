# TomatoJuice

**My reusable c code library**

## CONTAINS:
- Custom string type

## HOW TO USE:
Import one of the libraries into your project and include the associated header.

## REQUIREMENTS:
- C compiler with C23 support.

## SUPPORTED PLATFORMS
- Windows with MSVC
- Linux with gcc

## TODO SHORTTERM:
- More convenient string (owning)
    - Take a string_view of it (non-owning)
- write unit tests for string library
- write tests using a fuzzer

## NEXT STEPS:
- Make targets tests with/without asan.
- Can you test whether memory is uninitialized?
- What are the mocks from googlemock used for, sounds like more of a c++ thing, or can I for example provide a mock malloc to test allocations?


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
- Replace clang-format with clang-tidy
- Add support for mingw
- Add support for clang on linux
- Add support for clang-cl on windows

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