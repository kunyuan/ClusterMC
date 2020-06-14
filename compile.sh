#!/bin/bash
compiler=clang++
#compiler=icpc
#compiler=g++
#type=Debug
type=Release
#vcpkg_path=~/vcpkg/scripts/buildsystems/vcpkg.cmake
mkdir build
cd build

#with flag -n or -d or -nd
show_help(){
  cat<<EOF
  Usage: [-hnd]

    -h  display help information
    -n  clean up the build directory
    -d  turn on debug mode
EOF
}

_GETOPTS=":hnd"
OPTIND=1
while getopts "${_GETOPTS}" opt
do
  case $opt in
        d)
         type=Debug
         echo "Debug is ON"
         ;;
        n)
         rm -rf *
         echo "Clean up build direction"
         ;;
        h)
          show_help
          exit 0
          ;;
  esac
done

make clean
#cmake -DCMAKE_BUILD_TYPE=$type -DCMAKE_CXX_COMPILER=$compiler -DCMAKE_TOOLCHAIN_FILE=$vcpkg_path ..
cmake -DCMAKE_BUILD_TYPE=$type -DCMAKE_CXX_COMPILER=$compiler ..
make -j
make install
cd -
