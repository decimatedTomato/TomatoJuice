#!/bin/bash

if [[ $1 == "clean" ]]; then
    rm -rf src/build/
    rm -rf test/build/
    # cmake --build C:/foo/build/ --target clean
fi

set -xe
mkdir -p src/build
mkdir -p test/build
cd test/build
cmake .. -DCMAKE_BUILD_TYPE=Debug

if [[ $1 == "run" ]] || [[ $2 == "run" ]]; then
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        make
        cd -
        ./test/build/test_tomato_juice
    elif [[ "$OSTYPE" == "msys" ]]; then
        devenv.com test_tomato_juice.sln -Build
        cd -
        ./test/build/Debug/test_tomato_juice
    else
        exit 1
    fi
fi

# TODO add python integration tests