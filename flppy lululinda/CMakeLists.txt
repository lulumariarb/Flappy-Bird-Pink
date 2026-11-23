cmake_minimum_required(VERSION 3.16)

project(FlappyLululinda LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(flappy_lululinda
    src/main.cpp
    src/audio_manager.cpp
    src/game.cpp
    src/renderer.cpp
)

target_include_directories(flappy_lululinda PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_path(RAYLIB_INCLUDE_DIR raylib.h
    PATHS "C:/msys64/ucrt64/include" "C:/raylib/raylib/src" "C:/raylib/w64devkit/include"
)
find_library(RAYLIB_LIBRARY
    NAMES raylib libraylib
    PATHS "C:/msys64/ucrt64/lib" "C:/raylib/raylib/src" "C:/raylib/w64devkit/lib"
)

if(NOT RAYLIB_INCLUDE_DIR OR NOT RAYLIB_LIBRARY)
    message(FATAL_ERROR "raylib nao encontrado. Instale o raylib e configure RAYLIB_INCLUDE_DIR/RAYLIB_LIBRARY.")
endif()

target_include_directories(flappy_lululinda PRIVATE ${RAYLIB_INCLUDE_DIR})
target_link_libraries(flappy_lululinda PRIVATE ${RAYLIB_LIBRARY} opengl32 gdi32 winmm)
