#ifndef WINDOW_H
#define WINDOW_H

#include <memory>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class Window {
public:
    explicit Window(char const* title, int width = 640, int height = 480, SDL_WindowFlags flags = 0);

    static bool init();
    void quit();
private:
    std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window;
    std::unique_ptr<SDL_Surface, decltype(&SDL_DestroySurface)> m_screenSurface;
};

#endif //WINDOW_H
