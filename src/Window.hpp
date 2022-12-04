#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <SDL2/SDL.h>
#include <string>

class Window {
private:
    SDL_Window* window_ptr = nullptr;
    SDL_Renderer* renderer_ptr = nullptr;
    int m_isRunning;
public:
    Window(const std::string& name, int with, int height);
    ~Window();
    
    void close();
    bool isRunning();
    SDL_Renderer* getRendererPointer();

    const int m_width;
    const int m_height;
};

#endif // __WINDOW_H__