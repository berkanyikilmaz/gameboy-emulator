#include "window.h"

Window::Window(char const *title, int width, int height, SDL_WindowFlags flags)
    : m_window(SDL_CreateWindow(title, width, height, flags), &SDL_DestroyWindow)
    , m_screenSurface(SDL_GetWindowSurface(m_window.get()), &SDL_DestroySurface)
{
    if (!m_window) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL_CreateWindow Error: %s", SDL_GetError());
    }

    if (!m_screenSurface) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL_GetWindowSurface Error: %s", SDL_GetError());
    }
}

bool Window::init() {
    if (!SDL_InitSubSystem(SDL_INIT_VIDEO)) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL_InitSubSystem Error: %s", SDL_GetError());
        return false;
    }

    if (!TTF_Init()) {
        SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "TTF_Init Error");
        return false;
    }

    return true;
}

void Window::quit() {
    SDL_DestroyWindow(m_window.get());
    m_window = nullptr;
    m_screenSurface = nullptr;
    SDL_Quit();
}
