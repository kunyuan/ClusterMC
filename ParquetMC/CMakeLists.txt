cmake_minimum_required (VERSION 2.6)
project (ParquetMC)

file(GLOB_RECURSE SRCS *.cpp)

add_executable(parquet.exe  ${SRCS})

target_include_directories(parquet.exe PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/lib)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR})
# include_directories(${CMAKE_SOURCE_DIR}/lib)
# message("source dir:" ${FeynCalc_SOURCE_DIR})

# file(GLOB_RECURSE HDRS *.h)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/..") 
#crucial to output the .exe file to the root of project, and CLion compatible

# ADD_EXECUTABLE(feyncalc.exe  ${SRCS} ${HDRS})
# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

install (TARGETS parquet.exe DESTINATION ${CMAKE_SOURCE_DIR})