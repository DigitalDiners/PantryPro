cmake_minimum_required(VERSION 3.3.2)
project(MyApp C CXX)

include(cmake/App.cmake)

set(CMAKE_OSX_ARCHITECTURES x86_64)


set(SOURCES "src/MyApp.h"
            "src/MyApp.cpp"
            "src/main.cpp")

add_app("${SOURCES}")