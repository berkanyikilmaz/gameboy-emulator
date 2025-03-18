#ifndef DEBUG_H
#define DEBUG_H

#include <cstdint>
#include <iostream>

class Debug {
public:
    static void log(const char* msg, uint16_t data);

    static void logErr(const char* msg, uint16_t data);
};


#endif //DEBUG_H
