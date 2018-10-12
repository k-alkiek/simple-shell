cmake_minimum_required(VERSION 3.12)
project(simple_shell)

set(CMAKE_CXX_STANDARD 14)

add_executable(simple_shell src/main.cpp src/Logger.cpp include/Logger.h src/Shell.cpp include/Shell.h)