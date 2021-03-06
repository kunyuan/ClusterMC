cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
# set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3 -g")
# set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG")
# set(CMAKE_CXX_FLAGS_RELEASE "-Ofast -DNDEBUG")
#set(CMAKE_CXX_FLAGS_RELEASE "-march=native -ftree-vectorize -Ofast -g -DNDEBUG -mavx2 -mfma")

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wuninitialized")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wuninitialized" CACHE STRING "Set C++ Compiler Flags" FORCE)

add_subdirectory(ParquetMC)

set(PYBIND11_CPP_STANDARD -std=c++14)
set(pybind11_DIR "${CMAKE_SOURCE_DIR}/pybind11")

add_subdirectory(pybind11)

#build python module in lib
pybind11_add_module(grid ./lib/grid.cpp)
pybind11_add_module(green ./lib/green.cpp)

install(TARGETS grid DESTINATION "${CMAKE_SOURCE_DIR}")
install(TARGETS green DESTINATION "${CMAKE_SOURCE_DIR}")

#build python module in ParquetMC
pybind11_add_module(parquetMC
    ./ParquetMC/pybind.cpp
    ./ParquetMC/vertex4.cpp
    ./ParquetMC/vertex4_eval.cpp
    ./ParquetMC/propagator.cpp
)
target_include_directories(parquetMC PRIVATE ${CMAKE_SOURCE_DIR}/ParquetMC ${CMAKE_SOURCE_DIR}/lib)

install(TARGETS parquetMC DESTINATION "${CMAKE_SOURCE_DIR}")
