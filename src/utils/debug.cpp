#include "utils/debug.h"

void Debug::log(const char *msg, uint16_t data) {
    std::cout << std::format("->{}: {:04x}", msg, data) << std::endl;
}

void Debug::logErr(const char *msg, uint16_t data) {
    std::cerr << std::format("->{}: {:04x}", msg, data) << std::endl;
}
