cmake_minimum_required(VERSION 3.16)
project(sort)

set(CMAKE_CXX_STANDARD 20)

add_executable(sort main.cpp BubbleSort.h Tester.h CombSort.h QuickSort.h)