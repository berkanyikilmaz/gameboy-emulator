#include "emulator.h"

#include <common.h>
#include <iostream>
#include <SDL3/SDL.h>

Emulator::Emulator(int argc, char** argv)
: m_paused(false), m_running(true), m_ticks(0), m_window(nullptr)
, m_bus(nullptr), m_cpu(nullptr), m_cartridge(nullptr) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <rom file>" << std::endl;
        return;
    }

    Window::init();
    m_window = std::make_unique<Window>(Window("MyEmulator", 640, 480, SDL_WINDOW_RESIZABLE));

    m_cartridge = std::make_unique<Cartridge>(argv[1]);
    m_cpu = std::make_unique<CPU>(this);

    m_bus = std::make_unique<Bus>(m_cartridge.get(), m_cpu.get());
    m_cpu->connectBus(m_bus.get());
    m_cartridge->connectBus(m_bus.get());
}

void Emulator::run() {
    std::cout << "Running emulator" << std::endl;

    while (m_running) {
        // event polling
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                m_running = false;
            }
        }

        if (!m_cpu->step()) {
            std::cout << "CPU halted" << std::endl;
            m_running = false;
        }

        // cpu step
        m_ticks++;
    }

    m_window->quit();
}

void Emulator::cycle(int cycleCount) {
}
