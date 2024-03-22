cmake_minimum_required(VERSION 3.27)

# Set the cmake toolchain file
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

project("3D game" VERSION 1.0.0 DESCRIPTION "todo" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find SFML package
find_package(SFML COMPONENTS  window graphics)

include_directories(include Utils)
include_directories(include external)

add_executable(project classes/main.cpp
        classes/map.cpp headers/map.h
        headers/Player.h classes/Player.cpp
        Utils/Utils.cpp Utils/Utils.h
        headers/spriteRenderer.h classes/spriteRenderer.cpp
        headers/3dRender.h
        classes/3dRender.cpp
        headers/Stripe.h
        classes/Stripe.cpp
        classes/button.cpp
        headers/button.h
        headers/VisibleObject.h
        headers/Item.h
        classes/item.cpp)
target_link_libraries(project PRIVATE sfml-graphics sfml-window)