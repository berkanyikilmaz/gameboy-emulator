cmake_minimum_required(VERSION 3.30)
project(gameboy_cpp)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendors/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendors/SDL_ttf EXCLUDE_FROM_ALL)

add_executable(gameboy_cpp
        app/main.cpp
        src/emulator.cpp
        src/window.cpp)

target_include_directories(gameboy_cpp PRIVATE include)

target_link_libraries(gameboy_cpp PRIVATE
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf)
