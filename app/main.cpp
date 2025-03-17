#include <iostream>
#include "emulator.h"

int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;
    Emulator emulator;
    emulator.run(argc, argv);
    return 0;
}