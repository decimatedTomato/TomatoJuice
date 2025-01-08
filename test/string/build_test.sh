#!/bin/bash

gcc -o test/string/test_s8.exe test/string/test_s8.c string/*.c -Istring -Icommon -Werror -Wextra -Wall -pedantic -g