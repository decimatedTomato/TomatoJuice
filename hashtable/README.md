# Reusable hash table implementation

## TODO
- Test if this is the right directory for shared libs
- Figure out how to compile this as to make it easiest for me to use in other projects
- Add hashtable implementation (generics using macros I think)
- How to handle generic data
    - macro that regenerates the entire struct and interface with a naming suffix and using different data types
    - void* (-) causes indirection
    - A union between some common types one of which is void* 
    - _Generic I have to look into this but it seems to be used for tagged unions
    - codegen (nah)

- Add test scripts
- Use make for build system (different comp)

## How to use

### When Compiling
```sh
gcc program.c -I /c/MinGW/lib/gcc/x86_64-w64-mingw32/lib/ -L /c/MinGW/lib/gcc/x86_64-w64-mingw32/lib/TomatoJuice/hashtable/ -l hashtable
```
### In the code
```c
DEFINE_HASHTABLE(<type>)
```