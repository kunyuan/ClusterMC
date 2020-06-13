#!/bin/bash
compiler=clang++
#compiler=icpc
#compiler=g++
#type=Debug
type=Release
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

# OPTIND=1
# while getopts ":h:n:d:" opt; do
#      case $opt in
#          h)  show_help
#              exit 0
#              ;;
#          d)  type=Debug
#              echo "Debug Mode is ON"
#              ;;
#          n)  rm -rf *
#              echo "Clean up build directory"
#              ;;
#      esac
# done
# shift "$((OPTIND-1))"

# if [[ $* == *--flag*]]
# while :; do
#   case $1 in
#     -d|--debug)
#       echo "debug mode ON"
#       type=Debug
#       shift
#       # break
#       ;;
#     -n|--new)
#       echo "Clean up build directory"
#       rm -rf *
#       break
#       ;;
#   esac
#   # shift
# done

# if [ $@ = "-d"]; then
#   echo "find"
# else
#   echo "no"
# fi

# if [ -n "$1" ]
#   then
#   if [ $1 = "-n" ] || [ $1 = "--new" ]; then
#     make clean
#     rm -rf * #force to rerun cmake configuration
#     cmake -DCMAKE_BUILD_TYPE=$type -DCMAKE_CXX_COMPILER=$compiler ..
#   fi
# fi
make clean
cmake -DCMAKE_BUILD_TYPE=$type -DCMAKE_CXX_COMPILER=$compiler ..
make -j
make install
cd -
