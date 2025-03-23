#include "utils/debug.h"

void Debug::log(const char *msg, uint16_t data) {
    std::cout << std::format("{}: {:04X}", msg, data) << std::endl;
}

void Debug::log(const char *msg, uint8_t data) {
    std::cout << std::format("{}: {:02X}", msg, data) << std::endl;
}

void Debug::logErr(const char *msg, uint16_t data) {
    std::cerr << std::format("{}: {:04X}", msg, data) << std::endl;
}

void Debug::logErr(const char *msg, uint8_t data) {
    std::cerr << std::format("{}: {:02X}", msg, data) << std::endl;
}

void Debug::log(const char *msg) {
    std::cout << msg << std::endl;
}

void Debug::log(const std::string &msg) {
    std::cout << msg << std::endl;
}
