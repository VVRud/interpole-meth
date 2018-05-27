cmake_minimum_required(VERSION 3.10)
project(Interpolation)

set(GCC_COVERAGE_LINK_FLAGS "-I lib/Eigen/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
set(CMAKE_CXX_STANDARD 11)

file(GLOB LIBS
        lib/headers/*.h
        lib/*.cpp
        lib/*.hpp)

add_executable(Interpolation main.cpp ${LIBS} ${QT})
