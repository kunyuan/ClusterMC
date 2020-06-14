cmake_minimum_required (VERSION 2.6)
project (ParquetMC)

# file(GLOB_RECURSE SRCS *.cpp)

# add_executable(parquet.exe  ${SRCS})
add_executable(parquet.exe  
main.cpp
markov.cpp
observable.cpp 
propagator.cpp 
vertex4.cpp
vertex4_eval.cpp
vertex4_test.cpp
weight.cpp
group.cpp
diagram_polar.cpp
diagram_sigma.cpp
diagram_sigma.cpp
utility/logger.cpp)

target_include_directories(parquet.exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/lib)
install (TARGETS parquet.exe DESTINATION ${CMAKE_SOURCE_DIR})


# find_package(pybind11 CONFIG REQUIRED)
