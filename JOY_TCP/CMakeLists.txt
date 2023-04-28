cmake_minimum_required(VERSION 3.25)
project(JOY_TCP)

set(CMAKE_CXX_STANDARD 17)

add_executable(JOY_TCP main.cpp JoystickOnex.cpp)
