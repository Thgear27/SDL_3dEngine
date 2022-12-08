#include "MyEngine.hpp"
#include "myGL/Color.hpp"
#include "myGL/Matrix.hpp"
#include "myGL/Vector.hpp"
#include "myGL/myGL.hpp"
#include <iostream>
#include <limits>

const int width  = 960;
const int height = 720;

myEngine::myEngine()
    : window { "Ventana", width, height } {
    keyState = SDL_GetKeyboardState(nullptr);
    zbuffer = new float[window.m_width * window.m_height];
}

myEngine::~myEngine() {
    delete[] zbuffer;
}

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

    for (int i = 0; i < window.m_height * window.m_width; i++) {
        zbuffer[i] = -std::numeric_limits<float>::max();
    }

    float h = (3.14f * std::sin((float)SDL_GetTicks() / 1000));

    vec3f triangleVerts[] {
        vec3f { 0, 0.5f, 0 },      // 0
        vec3f { -0.5f, -0.5f, 0 }, // 1
        vec3f { 0.5f, -0.5f, 0 },  // 2
        vec3f { 0, 0.5f, -1 },     // 3
        vec3f { -0.5f, -0.5f, 0 }, // 4
        vec3f { 0.5f, -0.5f, 0 }   // 5
    };

    vec3f cube[] = {
        vec3f { -0.5f, -0.5f, -0.5f }, //
        vec3f { 0.5f, -0.5f, -0.5f },  //
        vec3f { 0.5f, 0.5f, -0.5f },   //

        vec3f { 0.5f, 0.5f, -0.5f },   //
        vec3f { -0.5f, 0.5f, -0.5f },  //
        vec3f { -0.5f, -0.5f, -0.5f }, //

        vec3f { -0.5f, -0.5f, 0.5f }, //
        vec3f { 0.5f, -0.5f, 0.5f },  //
        vec3f { 0.5f, 0.5f, 0.5f },   //

        vec3f { 0.5f, 0.5f, 0.5f },   //
        vec3f { -0.5f, 0.5f, 0.5f },  //
        vec3f { -0.5f, -0.5f, 0.5f }, //

        vec3f { -0.5f, 0.5f, 0.5f },   //
        vec3f { -0.5f, 0.5f, -0.5f },  //
        vec3f { -0.5f, -0.5f, -0.5f }, //

        vec3f { -0.5f, -0.5f, -0.5f }, //
        vec3f { -0.5f, -0.5f, 0.5f },  //
        vec3f { -0.5f, 0.5f, 0.5f },   //

        vec3f { 0.5f, 0.5f, 0.5f },   //
        vec3f { 0.5f, 0.5f, -0.5f },  //
        vec3f { 0.5f, -0.5f, -0.5f }, //

        vec3f { 0.5f, -0.5f, -0.5f }, //
        vec3f { 0.5f, -0.5f, 0.5f },  //
        vec3f { 0.5f, 0.5f, 0.5f },   //

        vec3f { -0.5f, -0.5f, -0.5f }, //
        vec3f { 0.5f, -0.5f, -0.5f },  //
        vec3f { 0.5f, -0.5f, 0.5f },   //

        vec3f { 0.5f, -0.5f, 0.5f },   //
        vec3f { -0.5f, -0.5f, 0.5f },  //
        vec3f { -0.5f, -0.5f, -0.5f }, //

        vec3f { -0.5f, 0.5f, -0.5f }, //
        vec3f { 0.5f, 0.5f, -0.5f },  //
        vec3f { 0.5f, 0.5f, 0.5f },   //

        vec3f { 0.5f, 0.5f, 0.5f },  //
        vec3f { -0.5f, 0.5f, 0.5f }, //
        vec3f { -0.5f, 0.5f, -0.5f } //
    };

    vec4f toSendCoords[36];

    Matrix rot           = rotatey(h);
    Matrix rot2          = rotatex(h);
    Matrix rot3          = rotatez(h);
    Matrix perpectiveMat = simpleProjection(120, width / height, 800);
    Matrix viewToWindow  = viewport(0, 0, window.m_width, window.m_height);

    Matrix ma1 = translate(window.m_width / 2, window.m_height / 2, 255 / 4);
    Matrix ma2 = translate(-window.m_width / 2, -window.m_height / 2, -255 / 4);

    for (int i = 0; i < 36; i++) {
        toSendCoords[i] = (ma1 * rot * rot2 * rot3 * ma2 * viewToWindow * perpectiveMat) * toHmgcoord(cube[i]);
    }

    window.clearScreen();
    for (int i = 0; i < 12; i++) {
        myGL::triangle(&toSendCoords[i * 3], &window, zbuffer);
    }

    // myGL::triangle(toSendCoords, &window);
    // myGL::triangle(&toSendCoords[3], &window);
    window.show();

}