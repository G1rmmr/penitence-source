cmake_minimum_required(VERSION 3.10)

project(ThePenitence VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_SOURCE_DIR}/cmake")

list(APPEND CMAKE_PREFIX_PATH C:/libs/SDL2)
find_package(SDL2 REQUIRED)

set(SOURCES
    main.cpp
)

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(ThePenitence ${SOURCES})

target_include_directories(ThePenitence PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(ThePenitence PRIVATE ${SDL2_LIBRARIES})
