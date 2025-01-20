#!/bin/bash

if [[ $1 == "clean" ]]; then
    rm -rf src/build/
    rm -rf test/build/
    shift 1
fi

mkdir -p src/build
mkdir -p test/build
cd test/build
cmake .. -DCMAKE_BUILD_TYPE
make
cd -

if [[ $1 == "run" ]]; then
    ./test/build/Debug/test_tomato_juice
fi
