cmake_minimum_required(VERSION 3.25)
project(QtTCP)

set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu")  # Qt 설치 경로
find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_executable(QtTCP main.cpp)

target_link_libraries(QtTCP Qt5::Widgets Qt5::Network)