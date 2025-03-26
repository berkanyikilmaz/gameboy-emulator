cmake_minimum_required(VERSION 3.30)
project(gameboy_cpp)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
        GIT_TAG        v0.9.7
)

FetchContent_MakeAvailable(magic_enum)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

add_subdirectory(vendors/SDL EXCLUDE_FROM_ALL)
add_subdirectory(vendors/SDL_ttf EXCLUDE_FROM_ALL)

add_executable(gameboy_cpp
        app/main.cpp
        src/emulator.cpp
        src/window.cpp
        src/cartridge.cpp
        src/utils/file_util.cpp
        src/bus.cpp
        src/cpu.cpp
        src/instructions.cpp
        src/utils/debug.cpp
        src/ram.cpp
        src/stack.cpp)

target_include_directories(gameboy_cpp PRIVATE include)

target_link_libraries(gameboy_cpp PRIVATE
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
        magic_enum::magic_enum)
