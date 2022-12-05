#include "Window.hpp"
#include "iostream"

Window::Window(const std::string& name, int width, int height)
    : m_width { width / 4 }
    , m_height { height / 4 } {
    window_ptr = SDL_CreateWindow(
        name.c_str(),           // Name
        SDL_WINDOWPOS_CENTERED, // X position
        SDL_WINDOWPOS_CENTERED, // Y position
        width,                  // Width
        height,                 // height
        SDL_WINDOW_OPENGL       // window type
    );

    renderer_ptr = SDL_CreateRenderer(window_ptr, -1, SDL_RENDERER_ACCELERATED);
    texture_ptr =
        SDL_CreateTexture(renderer_ptr, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, m_width, m_height);

    screenPixels = new Uint32[width * height];

    // pitch = 4 * m_width;
    // SDL_LockTexture(texture_ptr, nullptr, (void**)&screenPixels, &pitch);

    m_isRunning = true;
}

Window::~Window() {
    SDL_DestroyWindow(window_ptr);
    SDL_DestroyRenderer(renderer_ptr);
    SDL_DestroyTexture(texture_ptr);
    delete[] screenPixels;
}

void Window::close() { m_isRunning = false; }

bool Window::isRunning() { return m_isRunning; }

SDL_Renderer* Window::getRendererPointer() { return renderer_ptr; }

void Window::clearScreen() {
    for (int i = 0; i < m_width * m_height; i++) {
        screenPixels[i] = 0x0A0A0A;
    }
}

void Window::drawPixel(int x, int y, Color color) {
    if (x > m_width || y > m_height) return;
    if (x < 0 || y < 0) return;
    screenPixels[y * m_width + x] = color.raw;
}

void Window::show() {
    SDL_UpdateTexture(texture_ptr, nullptr, screenPixels, m_width * 4); // 4 bytes * m_width
    // SDL_UnlockTexture(texture_ptr);
    SDL_RenderCopy(renderer_ptr, texture_ptr, nullptr, nullptr);
    SDL_RenderPresent(renderer_ptr);
}