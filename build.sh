#!/bin/bash

# Conan install libraries packages
conan install . --build=missing -pr conan_profile_linux -if build
source build/activate.sh

# CMake build
cmake -B build -D CMAKE_MODULE_PATH=build

# Build
cmake --build build

# Copy Qt configuration file for run
cp build/qt.conf build/bin
