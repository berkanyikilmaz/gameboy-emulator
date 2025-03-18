#include "emulator.h"

#include <iostream>
#include <SDL3/SDL.h>

#include "cartridge.h"

Emulator::Emulator() : m_context{false, true, 0}, m_window(nullptr) {
    Window::init();
}

void Emulator::run(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <rom file>" << std::endl;
        return;
    }

    Cartridge cart(argv[1]);

    std::cout << "Running emulator" << std::endl;

    m_window = Window("MyEmulator", 640, 480, SDL_WINDOW_RESIZABLE);

    while (m_context.running) {
        // event polling
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                m_context.running = false;
            }
        }

        // cpu step
        m_context.ticks++;
    }

    m_window.quit();
}
