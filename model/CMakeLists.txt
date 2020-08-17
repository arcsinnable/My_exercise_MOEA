cmake_minimum_required(VERSION 3.16)
project(model)

set(CMAKE_CXX_STANDARD 14)

add_executable(model main.cpp global.cpp global.h initialize.cpp initialize.h reproduct.cpp reproduct.h)