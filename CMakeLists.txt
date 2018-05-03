cmake_minimum_required(VERSION 3.10)
project(Interpolation)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5Widgets)
list(APPEND THIRD_PARTY_LIBS Qt5::Widgets Qt5::Core)

set(GCC_COVERAGE_LINK_FLAGS "-I lib/Eigen/")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
set(CMAKE_CXX_STANDARD 11)

file(GLOB LIBS
        lib/*cpp
        lib/*h
        lib/*hpp)

file(GLOB QT
        desktop/mainwindow.h
        desktop/mainwindow.cpp)

add_executable(Interpolation main.cpp ${LIBS} ${QT})
target_link_libraries(${PROJECT_NAME}
        Qt5::Core
        Qt5::Widgets
        Qt5::Gui
        )
