cmake_minimum_required(VERSION 3.10)
project(SntKursach)

set(CMAKE_CXX_STANDARD 11)

file(GLOB LIBS lib/*cpp lib/*h lib/*hpp)

add_executable(SntKursach main.cpp ${LIBS})
