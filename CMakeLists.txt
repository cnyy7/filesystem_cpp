cmake_minimum_required(VERSION 3.14)
project(filesystem)

set(CMAKE_CXX_STANDARD 17)

add_executable(filesystem filesystem.h file.cpp dir.cpp main.cpp user.cpp system.cpp)