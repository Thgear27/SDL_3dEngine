#include "Window.hpp"

Window::Window(const std::string& name, int width, int height)
    : m_width { width }
    , m_height { height } {
    window_ptr = SDL_CreateWindow(
        name.c_str(),           // Name
        SDL_WINDOWPOS_CENTERED, // X position
        SDL_WINDOWPOS_CENTERED, // Y position
        width,                  // Width
        height,                 // height
        SDL_WINDOW_OPENGL       // window type
    );

    renderer_ptr = SDL_CreateRenderer(window_ptr, -1, SDL_RENDERER_ACCELERATED);
    m_isRunning  = true;
}

Window::~Window() {
    SDL_DestroyWindow(window_ptr);
    SDL_DestroyRenderer(renderer_ptr);
}

void Window::close() { m_isRunning = false; }

bool Window::isRunning() { return m_isRunning; }

SDL_Renderer* Window::getRendererPointer() { return renderer_ptr; }