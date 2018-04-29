cmake_minimum_required(VERSION 3.10)
project(SntKursach)

set(CMAKE_CXX_STANDARD 11)

file(GLOB LIBS lib/*cpp lib/*h)

add_executable(SntKursach main.cpp ${LIBS})
#add_executable(SntKursach spline/aspline.c spline/utils.c spline/utils.h)