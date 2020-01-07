cmake_minimum_required(VERSION 3.15)
project(hw3)

set(CMAKE_CXX_STANDARD 11)

add_executable(uniqueArr-Local ./provided_files/tests/UniqueArrayTest.cpp UniqueArray.h UniqueArrayImp.h)
add_executable(uniqueArr-Yuval ./provided_files/tests/OurUATests.cpp UniqueArray.h UniqueArrayImp.h)