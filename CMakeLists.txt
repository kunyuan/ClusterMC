cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
# set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g")
# set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG")
# set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG")
#set(CMAKE_CXX_FLAGS_RELEASE "-march=native -ftree-vectorize -Ofast -g -DNDEBUG -mavx2 -mfma")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wuninitialized")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wuninitialized" CACHE STRING "Set C++ Compiler Flags" FORCE)

set(PYBIND11_CPP_STANDARD -std=c++14)

# add_subdirectory(pybind11)
add_subdirectory(pybind)
add_subdirectory(ParquetMC)
