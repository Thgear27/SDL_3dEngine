#include "EventHandler.hpp"
#include <iostream>

EventHandler::EventHandler() {
    sdl_keyState = SDL_GetKeyboardState(nullptr);
}

EventHandler::~EventHandler() { }

bool EventHandler::isKeyPressed(SDL_Scancode key) {
    return sdl_keyState[key];
}

void EventHandler::updateEvent(SDL_Event& evt) {
    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT)
            quitEvent = true;
    }
}