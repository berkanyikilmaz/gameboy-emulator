#ifndef DEBUG_H
#define DEBUG_H

#include <cstdint>
#include <iostream>

namespace Debug {
    void log(const char* msg, uint16_t data);
    void log(const char* msg, uint8_t data);

    void logErr(const char* msg, uint16_t data);
    void logErr(const char *msg, uint8_t data);

    void log(const char* msg);
    void log(const std::string& msg);
};

#endif //DEBUG_H
