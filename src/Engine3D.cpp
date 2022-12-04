#include "Engine3D.hpp"
#include <iostream>

Engine3D::Engine3D() : window{ "HOLA", 1280, 720 }
{
    std::cout << "Engine3D creado" << '\n';
}

Engine3D::~Engine3D() {
    
}

void Engine3D::handleEvents() {
    SDL_Event evt; 
    eventHandler.updateEvent(evt);

    if(eventHandler.quitEvent) 
        window.close();

    if (eventHandler.isKeyPressed(SDL_SCANCODE_UP)) {
        std::cout << "UP key was pressed\n";
    }

    if (eventHandler.isKeyPressed(SDL_SCANCODE_DOWN)) {
        std::cout << "DOWN key was pressed\n";
    }
}

void Engine3D::update() {
    
}

void Engine3D::renderAll() {
    
}

bool Engine3D::isRunning() {
    return window.isRunning();
}
