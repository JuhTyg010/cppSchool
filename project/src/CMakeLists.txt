cmake_minimum_required(VERSION 3.27)
project("3D game" VERSION 1.0.0 DESCRIPTION "todo" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


find_package(SFML COMPONENTS graphics audio window REQUIRED)
include_directories(include Utils)

add_executable(demo classes/main.cpp
)
target_link_libraries(demo sfml-graphics sfml-audio sfml-window)

add_executable(project classes/main.cpp
        classes/map.cpp headers/map.h
        headers/Player.h classes/Player.cpp
        Utils/Utils.cpp Utils/Utils.h
        headers/spriteRenderer.h classes/spriteRenderer.cpp
        headers/3dRender.h
        classes/3dRender.cpp
        headers/Stripe.h
        classes/Stripe.cpp)
target_link_libraries(project sfml-graphics sfml-audio sfml-window)