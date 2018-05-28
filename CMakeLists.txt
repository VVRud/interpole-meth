cmake_minimum_required(VERSION 3.10)
project(Interpolation)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)
find_package(Qt5PrintSupport REQUIRED)

list(APPEND THIRD_PARTY_LIBS Qt5::Widgets Qt5::Core)

set(GCC_COVERAGE_LINK_FLAGS "-I lib/Eigen/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
set(CMAKE_CXX_STANDARD 11)

file(GLOB LIBS
        lib/headers/*.h
        lib/*.cpp
        lib/*.hpp)

file(GLOB QT
        desktop/*.h
        desktop/*.cpp)

file(GLOB PLOT
        lib/QCustomPlot/qcustomplot.h
        lib/QCustomPlot/qcustomplot.cpp)

add_executable(Interpolation main.cpp ${LIBS} ${QT} ${PLOT})
target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        Qt5::PrintSupport
        )
