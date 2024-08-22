# Define minimum version of CMake
cmake_minimum_required(VERSION 3.24)

# Set project
project(ThePenitence
  	VERSION 0.1
  	DESCRIPTION "First Game of the BLAKCHAND Studio."
  	LANGUAGES CXX)

# Set C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set SDLs
include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)

# SDL2
FetchContent_Declare(SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.26.3
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(SDL2)

# SDL2 Image
FetchContent_Declare(SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG release-2.6.3
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(SDL2_image)

# Add library search
add_subdirectory(lib)

# Make exe
add_executable(ThePenitence main.cpp)

# Link header and library
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

target_include_directories(ThePenitence PUBLIC
    ${CMAKE_SOURCE_DIR}/includes
	${SDL2_SOURCE_DIR}/include
    ${SDL2_IMAGE_SOURCE_DIR}/include)

target_link_libraries(ThePenitence PRIVATE
    GAlpha
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image::SDL2_image)
    
target_compile_options(ThePenitence PRIVATE -Wall -Werror)