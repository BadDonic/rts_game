cmake_minimum_required(VERSION 3.8)
project(courseWork)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
include_directories(TinyXML)

file(GLOB SOURCES "main.cpp" "src/*.cpp" "include/*.h" "TinyXML/*.h" "TinyXML/*.cpp")
add_executable(courseWork ${SOURCES} include/icon.h)
target_link_libraries(courseWork "-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio")