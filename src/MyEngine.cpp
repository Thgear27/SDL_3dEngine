#include "MyEngine.hpp"
#include <iostream>

myEngine::myEngine() : window{ "HOLA", 1280, 720 }
{
    std::cout << "Engine3D creado" << '\n';
}

myEngine::~myEngine() {
    
}

void myEngine::handleEvents() {
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

void myEngine::update() {

}

void myEngine::renderAll() {
}

bool myEngine::isRunning() {
    return window.isRunning();
}
