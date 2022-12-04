#include "MyEngine.hpp"
#include <iostream>

myEngine::myEngine() : window{ "Ventana", 1280, 720 } {}

myEngine::~myEngine() {}

void myEngine::handleEvents() {
    SDL_Event evt; 
    eventHandler.updateEvent(evt);

    if(eventHandler.quitEvent) 
        window.close();

    if(eventHandler.isKeyPressed(SDL_SCANCODE_ESCAPE))
        window.close();
}

bool myEngine::isRunning() {
    return window.isRunning();
}

///////////////////////////////////////////////////////////////////
//// RENDER FUNCTIONS

void drawPixel(int x, int y, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(renderer, x, y);
    SDL_RenderPresent(renderer);
}

void clearScreen(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
}

void myEngine::renderAll() {
    SDL_Renderer* renderer = window.getRendererPointer();
    clearScreen(renderer);
    drawPixel(20, 20, renderer);
}