# Define minimum version of CMake
cmake_minimum_required(VERSION 3.24)

# Set project
project(ThePenitence
    VERSION 0.1
    DESCRIPTION "First Game of the BLAKCHAND Studio."
    LANGUAGES CXX)

# Set C++ standard
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

set(SDL2IMAGE_INSTALL OFF)
set(BUILD_SHARED_LIBS FALSE)
FetchContent_MakeAvailable(SDL2_image)

# Add library search
add_subdirectory(lib)

# Make exe
add_executable(ThePenitence main.cpp)

# Link header and library
target_include_directories(ThePenitence PUBLIC
    ${CMAKE_SOURCE_DIR}/includes
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS})

target_link_libraries(ThePenitence PUBLIC
    GAlpha
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_image)

# Compile opt
target_compile_options(ThePenitence PRIVATE -Wall -Werror)

# Export sets
install(TARGETS SDL2 SDL2main SDL2-static SDL2_image
    EXPORT SDL2Exports
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
    PUBLIC_HEADER DESTINATION include/SDL2)