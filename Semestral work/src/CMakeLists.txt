cmake_minimum_required(VERSION 3.28)
project(Semestral_work)

set(CMAKE_CXX_STANDARD 20)

add_executable(Semestral_work main.cpp unsolvedGrids.h solvedGrids.h
        sudokuSolver.h sudokuSolver.cpp
        randomSolver.h randomSolver.cpp
        neighborSolver.h neighborSolver.cpp
        changeWorstSolver.h changeWorstSolver.cpp
        minimizeSolver.h minimizeSolver.cpp)

add_compile_options(-fsanitize=address -fsanitize=undefined -g -O2)