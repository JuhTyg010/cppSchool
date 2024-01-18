cmake_minimum_required(VERSION 3.27)
project("3D game" VERSION 1.0.0 DESCRIPTION "todo" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(SFML COMPONENTS graphics audio window REQUIRED)
include_directories(include)

add_executable(demo main.cpp
        object.h object.cpp)
target_link_libraries(demo sfml-graphics sfml-audio sfml-window)
