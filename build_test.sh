#!/bin/bash

set -e

if [[ $1 == "clean" ]]; then
    rm -rf bin
    shift 1
fi

mkdir -p bin
cmake -S . -B bin -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build bin

if [[ $1 == "run" ]]; then
    # ./bin/test/test_tomato_juice --gtest_break_on_failure
    ./bin/test/test_tomato_juice
fi
