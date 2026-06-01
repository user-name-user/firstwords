#!/bin/bash

echo "Refreshing build/ contents and running command: cd build"
rm -rf build
mkdir build
cd build

echo "Running command: cmake .."
cmake ..

echo "Running command: make"
make