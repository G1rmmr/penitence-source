cmake_minimum_required(VERSION 3.10)
project(penitence)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(SFML_ROOT "${CMAKE_SOURCE_DIR}/libs/SFML")

include_directories(
    "${CMAKE_SOURCE_DIR}/include"
    "${SFML_ROOT}/include")

file(GLOB_RECURSE PROJECT_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

set(SFML_LIB_DIR "${SFML_ROOT}/lib")
link_directories("${SFML_LIB_DIR}")

set(SFML_LIBS sfml-graphics sfml-window sfml-system sfml-audio)

if(WIN32)
    add_custom_command(TARGET penitence POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SFML_LIB_DIR}"
        $<TARGET_FILE_DIR:penitence>)
endif()

add_executable(penitence ${PROJECT_SOURCES})
target_link_libraries(penitence ${SFML_LIBS})