cmake_minimum_required(VERSION 3.27)

# Project name and a few useful settings. Other commands can pick up the results
project(MyGame VERSION 0.0.1)

# Add the devlibs directories to the paths used to find libraries and programs.
# list(APPEND CMAKE_PREFIX_PATH "C:/Devlibs")

set( SOURCE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src" )
set( INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/src" )

# Add the devlibs directories to the paths used to find libraries and programs.
# list(APPEND CMAKE_PREFIX_PATH "R:/Documentos/Program/Cpp/SDL3/vendor/SDL_ttf")
# find_package(SDL3 REQUIRED)
# Find FreeType

# Debugging output to verify paths
# message(STATUS "FREETYPE_INCLUDE_DIRS: ${FREETYPE_INCLUDE_DIRS}")
# message(STATUS "FREETYPE_LIBRARIES: ${FREETYPE_LIBRARIES}")
#include_directories(${SDL2_INCLUDE_DIRS})
#add_executable(Tetris src/main.cpp)
# Add SDL3 as a subdirectory
set(SDL_DISABLE_INSTALL ON CACHE BOOL "Do not install SDL3")
add_subdirectory(vendor/SDL/ EXCLUDE_FROM_ALL)
# Add SDL_ttf directory
set(SDLTTF_VENDORED ON CACHE BOOL "Use vendored FreeType")
set(SDLTTF_SDL3_DEPENDENCY_TYPE "cmake" CACHE STRING "Force SDL_ttf to use CMake target for SDL3")
set(SDLTTF_SDL3_PATH "${CMAKE_CURRENT_BINARY_DIR}/vendor/SDL" CACHE PATH "Path to SDL3 build directory")
add_subdirectory(vendor/SDL_ttf/)
# find_package(SDL3_ttf CONFIG REQUIRED)

# Add SDL_image directory and ensure it uses the vendored SDL3
set(SDLIMAGE_VENDORED ON CACHE BOOL "Use vendored dependencies in SDL_image")
set(SDLIMAGE_SDL3_DEPENDENCY_TYPE "cmake" CACHE STRING "Force SDL_image to use CMake target for SDL3")
set(SDLIMAGE_SDL3_PATH "${CMAKE_CURRENT_BINARY_DIR}/vendor/SDL" CACHE PATH "Path to SDL3 build directory")

set(SDLIMAGE_AVIF OFF CACHE BOOL "Disable AVIF support (dav1d requires NASM)")
set(SDLIMAGE_WEBP OFF CACHE BOOL "Disable WebP support")
set(SDLIMAGE_JXL OFF CACHE BOOL "Disable JPEG XL support")
set(SDLIMAGE_HEIF OFF CACHE BOOL "Disable HEIF support")
add_subdirectory(vendor/SDL_image/)

add_executable(Tetris)

target_sources(
    Tetris
    PRIVATE
       "${SOURCE_PATH}/main.cpp"
       "${SOURCE_PATH}/game.cpp"
       "${SOURCE_PATH}/grid.cpp"
       "${SOURCE_PATH}/block.cpp"
    PUBLIC
)

target_link_libraries(
    Tetris
    PRIVATE
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
        SDL3_image::SDL3_image
)

if(CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET Tetris PROPERTY CXX_STANDARD 20)
endif()