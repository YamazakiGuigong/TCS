cmake_minimum_required(VERSION 3.10)

project(Snake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(cpp-terminal)

add_executable(Snake Snake.cpp)
target_link_libraries(Snake PRIVATE cpp-terminal)