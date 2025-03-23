#include <iostream>
#include "emulator.h"

int main(int argc, char** argv) {
    std::cout << "Hello, World!" << std::endl;

    Emulator emulator(argc, argv);
    emulator.run();
    return 0;


}