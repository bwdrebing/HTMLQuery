cmake_minimum_required(VERSION 3.19)

#Create a cpp project named CMake_Example 
project(HTMLQuery C CXX)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake/")

#Tell CMake to build src/ 
add_subdirectory(src)
add_subdirectory(test)
