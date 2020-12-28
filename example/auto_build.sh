#!/bin/bash
rm -rf build
mkdir build
mkdir log
cd build
cmake ..
make -j
cd ..
