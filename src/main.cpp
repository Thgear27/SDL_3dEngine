#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "MyEngine.hpp"
#include "Renderer.hpp"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    myEngine myEngineIntance;

    while (myEngineIntance.isRunning()) {
        myEngineIntance.handleEvents();
        myEngineIntance.update();
        myEngineIntance.renderAll();
    }

    SDL_Quit();
    return 0;
}