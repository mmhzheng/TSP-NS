#!/bin/bash
mkdir build
mkdir log
cd build
cmake ..
make -j
cd ..
