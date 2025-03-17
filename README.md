# gameboy-emulator

# Notes
-> You should clone the repository with --recursive flag is enabled as vendors are retrieved as submodules. If you have cloned the repository without it, use the command belove to get those:

git submodule update --init


-> After cloning, use the terminal commands below to build the emulator:

cmake -S . -B build
cmake --build build

-> To run the build, use the below command:

cd build
./gameboy_cpp
