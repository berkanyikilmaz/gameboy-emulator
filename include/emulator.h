#ifndef EMULATOR_H
#define EMULATOR_H

#include <cstdint>
#include <memory>

#include "window.h"
#include "bus.h"
#include "cpu.h"
#include "cartridge.h"
#include "ram.h"

class Emulator {
public:
    Emulator(int argc, char** argv);

    void run();
    void cycle(int cycleCount);
private:
    bool m_paused;
    bool m_running;
    uint64_t m_ticks;

    std::unique_ptr<Window> m_window;
    std::unique_ptr<Bus> m_bus;
    std::unique_ptr<CPU> m_cpu;
    std::unique_ptr<Cartridge> m_cartridge;
    std::unique_ptr<RAM> m_ram;
};

#endif //EMULATOR_H
