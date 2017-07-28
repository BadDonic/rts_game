cmake_minimum_required(VERSION 3.8)
project(courseWork)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

file(GLOB SOURCES "main.cpp" "src/*.cpp" "include/*.h")
add_executable(courseWork ${SOURCES})
target_link_libraries(courseWork "-lsfml-graphics -lsfml-window -lsfml-system")