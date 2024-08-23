cmake_minimum_required(VERSION 3.24)
cmake_policy(SET CMP0028 NEW)

# Set Project
project(ThePenitence LANGUAGES CXX)
set(PROJECT_NAME "ThePenitence" CACHE STRING "Project name.")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set dir
add_subdirectory(lib)

# Define executable
add_executable(${PROJECT_NAME} main.cpp)

# Fetch SDL2s
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-2.26.0
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(SDL2)

FetchContent_Declare(SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image
    GIT_TAG release-2.6.3
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)

set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)

FetchContent_MakeAvailable(SDL2_image)

# Link libs
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/includes
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    GAlpha
    SDL2::SDL2main
    SDL2::SDL2-static
    SDL2_image::SDL2_image-static)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror)