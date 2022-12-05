#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "MyEngine.hpp"
#include "myGL/Matrix.hpp"
#include "myGL/Vector.hpp"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    myEngine myEngineIntance;

    Uint32 startTime, frame_time;

    while (myEngineIntance.isRunning()) {
        startTime = SDL_GetTicks64();
        myEngineIntance.handleEvents();
        myEngineIntance.renderAll();
        frame_time = SDL_GetTicks64() - startTime;
        std::cerr << 1000.f / frame_time << '\n';
    }

    SDL_Quit();
    return 0;
}