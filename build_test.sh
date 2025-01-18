#!/bin/bash

set -xe

# rm -rf src/build/
# rm -rf test/build/

mkdir -p src/build
mkdir -p test/build
cd test/build
cmake .. #-DCMAKE_BUILD_TYPE=Debug
devenv.com test_tomato_juice.sln -Build
cd -
./test/build/Debug/test_tomato_juice