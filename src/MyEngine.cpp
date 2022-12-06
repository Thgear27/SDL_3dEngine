#include "MyEngine.hpp"
#include "myGL/Color.hpp"
#include "myGL/Matrix.hpp"
#include "myGL/Vector.hpp"
#include "myGL/myGL.hpp"
#include <iostream>

const int width  = 960;
const int height = 720;

myEngine::myEngine()
    : window { "Ventana", width, height } {
    keyState = SDL_GetKeyboardState(nullptr);
}

myEngine::~myEngine() {}

void myEngine::handleEvents() {
    SDL_Event evt;

    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) window.close();
    }

    if (keyState[SDL_SCANCODE_ESCAPE]) window.close();
    if (keyState[SDL_SCANCODE_UP]) std::cout << "UP\n";
}

bool myEngine::isRunning() { return window.isRunning(); }

///////////////////////////////////////////////////////////////////
//// RENDER FUNCTIONS

void myEngine::renderAll() {

    float h = (3.14f * std::sin((float)SDL_GetTicks() / 1000));

    vec3f triangleVerts[] {
        vec3f { 50, 50, -20 },  //
        vec3f { 170, 90, -20 }, //
        vec3f { 50, 130, -20 }  //
    };

    vec4f toSendCoords[3];

    Matrix rot = rotatey(h);
    Matrix rot2 = rotatex(h);
    Matrix rot3 = rotatez(h);
    Matrix perpective = simpleProjection(800);

    Matrix ma1 = translate(window.m_width / 2, window.m_height / 2, 0);
    Matrix ma2 = translate(-window.m_width / 2, -window.m_height / 2, 0);

    for (int i = 0; i < 3; i++) {
        toSendCoords[i] = ma1 * rot * rot2 * rot3 * ma2 * perpective * toHmgcoord(triangleVerts[i]);
    }

    window.clearScreen();
    myGL::triangle(toSendCoords, &window);
    window.show();
}