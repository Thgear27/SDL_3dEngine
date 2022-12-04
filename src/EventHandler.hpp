#ifndef __EVENTHANDLER_H__
#define __EVENTHANDLER_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_keyboard.h>

struct EventHandler {
    const Uint8* sdl_keyState;

    bool quitEvent = false;

    EventHandler();
    ~EventHandler();

    bool isKeyPressed(SDL_Scancode key);
    void updateEvent(SDL_Event& evt);
    bool isEventOn(SDL_EventType evtType);
};

#endif // __EVENTHANDLER_H__