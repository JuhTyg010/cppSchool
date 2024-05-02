cmake_minimum_required(VERSION 3.27)

# Set the cmake toolchain file

project("3D game" VERSION 1.0.0 DESCRIPTION "collect or escape the game" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# Find SFML package
find_package(SFML COMPONENTS  window graphics)

include_directories(include Utils, headers)

set(RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Utils)
set(RESOURCE_FONT Montserrat-Regular.ttf)

function(copy_font target)
    add_custom_command(TARGET ${target}
            POST_BUILD COMMAND
            ${CMAKE_COMMAND} -E copy ${RESOURCE_DIR}/${RESOURCE_FONT} ${CMAKE_CURRENT_BINARY_DIR}/)
endfunction()

add_executable(project classes/main.cpp
        classes/map.cpp
        classes/Player.cpp
        Utils/Utils.cpp Utils/Utils.h
        classes/spriteRenderer.cpp
        classes/3dRender.cpp
        classes/Stripe.cpp
        classes/button.cpp headers/button.h
        classes/item.cpp
        classes/UIText.cpp)
target_link_libraries(project PRIVATE sfml-graphics sfml-window)
copy_font(project)

add_executable(editor MapGeneration/MapGenerator.cpp)
target_link_libraries(editor PRIVATE sfml-graphics sfml-window)
copy_font(editor)