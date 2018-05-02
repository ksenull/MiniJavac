cmake_minimum_required(VERSION 3.1)
project(MINIJAVAC)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(ast)
add_subdirectory(symboltable)
add_subdirectory(ir)
add_subdirectory(common)