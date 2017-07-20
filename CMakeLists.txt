cmake_minimum_required(VERSION 3.8)
project(courseWork)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(courseWork ${SOURCE_FILES})
target_link_libraries(courseWork "-lsfml-graphics -lsfml-window -lsfml-system")