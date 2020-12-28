#!/bin/bash

git submodule update --init --recursive

mkdir lib/g3log/build
cd lib/g3log/build
cmake ..
make -j
sudo make install
cd -