#include "MyEngine.hpp"
#include <iostream>

myEngine::myEngine() : window{ "Ventana", 1280, 720 } {
    keyState = SDL_GetKeyboardState(nullptr);
}

myEngine::~myEngine() {}

void myEngine::handleEvents() {
    SDL_Event evt; 

    while (SDL_PollEvent(&evt)) {
        if(evt.type == SDL_QUIT) 
            window.close();
    }

    if(keyState[SDL_SCANCODE_ESCAPE])
        window.close();
    if(keyState[SDL_SCANCODE_UP])
        std::cout << "UP\n";
}

bool myEngine::isRunning() {
    return window.isRunning();
}

///////////////////////////////////////////////////////////////////
//// RENDER FUNCTIONS

void drawPixel(int x, int y, SDL_Renderer* renderer) {
    SDL_RenderDrawPoint(renderer, x, y);
}

void line(int x1, int y1, int x2, int y2, SDL_Renderer* renderer) {
    bool inverted_plane = false;
    if (std::abs(y2 - y1) > std::abs(x2 - x1)) { // Triangulo con pendiente mayor a 1
        std::swap(x1, y1);
        std::swap(x2, y2);
        inverted_plane = true;
    }

    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    // Bresenham's algorithm
    int dx = x2 - x1;
    int dy = y2 - y1;
    int dxe = std::abs(dy) - std::abs(dx);
    int y = y1; // punto inicial que ira aumentando
    for (int x = x1; x <= x2; x++) {
        if (!inverted_plane)
            drawPixel(x, y, renderer);
        else
            drawPixel(y, x, renderer);

        dxe += std::abs(dy);

        if (dxe > 0) {
            dxe -= dx;
            y += (y2 > y1) ? 1 : -1;
        }
    }
}

void clearScreen(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void myEngine::renderAll() {
    SDL_Renderer* renderer = window.getRendererPointer();
    clearScreen(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    line(20, 20, 50, 50, renderer);
    line(50, 50, 20, 90, renderer);
    SDL_RenderPresent(renderer);
}