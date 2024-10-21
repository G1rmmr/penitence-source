cmake_minimum_required(VERSION 3.10)

project(penitence LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

file(GLOB_RECURSE SRC_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.c"
)

message(STATUS "Source files found: ${SRC_FILES}")

if(NOT SRC_FILES)
    message(FATAL_ERROR "No source files found in Src/ directory.")
endif()

add_executable(penitence ${SRC_FILES})

set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/libs/sdl2/include")
set(SDL2_LIB_DIR "${CMAKE_SOURCE_DIR}/libs/sdl2/lib")

message(STATUS "SDL2 include directory: ${SDL2_INCLUDE_DIR}")
message(STATUS "SDL2 library directory: ${SDL2_LIB_DIR}")

target_include_directories(penitence PRIVATE "${SDL2_INCLUDE_DIR}")

if(WIN32)
    set(SDL2_LIBS "${SDL2_LIB_DIR}/libSDL2.lib" "${SDL2_LIB_DIR}/libSDL2main.a")
elseif(APPLE)
    set(SDL2_LIBS "${SDL2_LIB_DIR}/libSDL2.dylib" "${SDL2_LIB_DIR}/libSDL2main.a")
else()
    set(SDL2_LIBS "${SDL2_LIB_DIR}/libSDL2.so")
endif()

message(STATUS "SDL2 libraries to link: ${SDL2_LIBS}")

target_link_libraries(penitence PRIVATE ${SDL2_LIBS})

if(APPLE)
    set_target_properties(penitence PROPERTIES
        MACOSX_RPATH "@executable_path/../libs/sdl2/lib"
    )
elseif(UNIX)
    set_target_properties(penitence PROPERTIES
        INSTALL_RPATH "${CMAKE_SOURCE_DIR}/libs/sdl2/lib"
    )
endif()

if(WIN32)
    target_compile_definitions(penitence PRIVATE SDL_MAIN_HANDLED)

    add_custom_command(TARGET penitence POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_LIB_DIR}/SDL2.dll"
            $<TARGET_FILE_DIR:penitence>)
endif()