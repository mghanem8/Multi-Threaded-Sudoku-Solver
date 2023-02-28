cmake_minimum_required(VERSION 3.23)
project(Lab1P2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab1P2
        main.cpp
        SudokuGrid.cpp
        SudokuGrid.h)
