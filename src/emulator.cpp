#include "emulator.h"

#include <iostream>
#include <SDL3/SDL.h>

Emulator::Emulator() : m_context{false, true, 0}, m_window(nullptr) {
    Window::init();
}

void Emulator::run(int argc, char** argv) {
    std::cout << "Running emulator" << std::endl;

    m_window = Window("MyEmulator", 640, 480, SDL_WINDOW_RESIZABLE);

    while (m_context.running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                m_context.running = false;
            }
        }
    }

    m_window.quit();
}
