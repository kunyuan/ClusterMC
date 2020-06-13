cmake_minimum_required(VERSION 2.8.12)
project(grid)

set(CMAKE_CXX_STANDARD 14)

# find_package(pybind11 CONFIG REQUIRED)
# target_link_libraries(main PRIVATE mylib pybind11::embed pybind11::module pybind11::pybind11)

add_subdirectory(pybind11)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/..") 
pybind11_add_module(grid grid.cpp)
pybind11_add_module(green green.cpp)

# include_directories("../../ParquetMC/")

pybind11_add_module(vertex tree.cpp
    ../../ParquetMC/vertex4.cpp
    ../../ParquetMC/vertex4_eval.cpp
    ../../ParquetMC/propagator.cpp
)
target_include_directories(vertex PRIVATE ${CMAKE_SOURCE_DIR}/ParquetMC ${CMAKE_SOURCE_DIR}/lib)

install(TARGETS grid DESTINATION "${CMAKE_SOURCE_DIR}")
install(TARGETS green DESTINATION "${CMAKE_SOURCE_DIR}")
install(TARGETS vertex DESTINATION "${CMAKE_SOURCE_DIR}")


