#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "Engine3D.hpp"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    Engine3D myEngineIntance;

    while (myEngineIntance.isRunning()) {
        myEngineIntance.handleEvents();
        myEngineIntance.update();
        myEngineIntance.renderAll();
    }

    SDL_Quit();
    return 0;
}