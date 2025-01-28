#!/bin/bash

set -e

if [[ $1 == "clean" ]]; then
    rm -rf src/build/
    rm -rf test/build/
    shift 1
fi

mkdir -p src/build
mkdir -p test/build
cmake -S test -B test/build -DCMAKE_BUILD_TYPE=BUILD
cmake --build test/build

if [[ $1 == "run" ]]; then
    ./test/build/test_tomato_juice
fi
