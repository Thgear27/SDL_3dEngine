#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SDL2/SDL.h>
#include <string>
#include "myGL/Color.hpp"

class Window {
private:
    SDL_Window* window_ptr     = nullptr;
    SDL_Renderer* renderer_ptr = nullptr;
    SDL_Texture* texture_ptr   = nullptr;

    Uint32* screenPixels;
    // int pitch;

    int m_isRunning;
public:
    Window(const std::string& name, int with, int height);
    ~Window();

    void close();
    bool isRunning();
    SDL_Renderer* getRendererPointer();
    void clearScreen();
    void drawPixel(int x, int y, Color color);
    void show();

    const int m_width;
    const int m_height;
};

#endif // __WINDOW_H__