#ifndef EMULATOR_H
#define EMULATOR_H

#include <cstdint>

#include "window.h"

struct EmulatorContext {
    bool paused;
    bool running;
    uint64_t ticks;
};

class Emulator {
public:
    Emulator();

    void run(int argc, char** argv);

    const EmulatorContext& getContext() const { return m_context; }
private:
    EmulatorContext m_context;
    Window m_window;
};

#endif //EMULATOR_H
