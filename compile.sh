#!/bin/bash
#compiler=clang++
compiler=icpc
#compiler=g++
#type=Debug
type=Release
mkdir build
cd build
if [ -n "$1" ]
  then
  if [ $1 = "-n" ] || [ $1 = "--new" ]; then
    make clean
    rm -rf * #force to rerun cmake configuration
    cmake -DCMAKE_BUILD_TYPE=$type -DCMAKE_CXX_COMPILER=$compiler ..
  fi
fi
make -j
make install
cd -
