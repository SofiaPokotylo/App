cmake_minimum_required(VERSION 3.21)
project(App)

set(CMAKE_CXX_STANDARD 14)

add_executable(App main.cpp search.cpp)

add_library(search_library STATIC search.cpp search.h)
