#include "MyEngine.hpp"
#include "myGL/Color.hpp"
#include "myGL/Matrix.hpp"
#include "myGL/Vector.hpp"
#include "myGL/myGL.hpp"
#include <iostream>
#include <limits>

const int width  = 920;
const int height = 720;

myEngine::myEngine()
    : window { "Ventana", width, height }
    , texture { "imgs/wood.jpg" } {
    keyState = SDL_GetKeyboardState(nullptr);
    zbuffer  = new float[window.m_width * window.m_height];
}

myEngine::~myEngine() { delete[] zbuffer; }

void myEngine::handleEvents() {
    SDL_Event evt;

    while (SDL_PollEvent(&evt)) {
        if (evt.type == SDL_QUIT) window.close();
    }

    if (keyState[SDL_SCANCODE_ESCAPE]) window.close();
    if (keyState[SDL_SCANCODE_UP]) v3 += 0.1f;
    if (keyState[SDL_SCANCODE_DOWN]) v3 -= 0.1f;
    if (keyState[SDL_SCANCODE_RIGHT]) v1 += 0.1f;
    if (keyState[SDL_SCANCODE_LEFT]) v1 -= 0.1f;
    if (keyState[SDL_SCANCODE_W]) v2 += 0.1f;
    if (keyState[SDL_SCANCODE_S]) v2 -= 0.1f;
}

bool myEngine::isRunning() { return window.isRunning(); }

///////////////////////////////////////////////////////////////////
//// RENDER FUNCTIONS

void myEngine::renderAll() {

    for (int i = 0; i < window.m_height * window.m_width; i++) {
        zbuffer[i] = -std::numeric_limits<float>::max();
    }

    float h = (3.14f * std::sin((float)SDL_GetTicks() / 1000));

    vec3f cube[] = {
        vec3f { 0.5f, -0.5f, -0.5f },  // BIEN
        vec3f { -0.5f, -0.5f, -0.5f }, //
        vec3f { 0.5f, 0.5f, -0.5f },   //

        vec3f { -0.5f, 0.5f, -0.5f },  // BIEN
        vec3f { 0.5f, 0.5f, -0.5f },   //
        vec3f { -0.5f, -0.5f, -0.5f }, //

        vec3f { -0.5f, -0.5f, 0.5f }, // BIEN
        vec3f { 0.5f, -0.5f, 0.5f },  //
        vec3f { 0.5f, 0.5f, 0.5f },   //

        vec3f { 0.5f, 0.5f, 0.5f },   // BIEN
        vec3f { -0.5f, 0.5f, 0.5f },  //
        vec3f { -0.5f, -0.5f, 0.5f }, //

        vec3f { -0.5f, 0.5f, 0.5f },   // BIEN
        vec3f { -0.5f, 0.5f, -0.5f },  //
        vec3f { -0.5f, -0.5f, -0.5f }, //

        vec3f { -0.5f, -0.5f, -0.5f }, // BIEN
        vec3f { -0.5f, -0.5f, 0.5f },  //
        vec3f { -0.5f, 0.5f, 0.5f },   //

        vec3f { 0.5f, 0.5f, -0.5f },  // BIEN
        vec3f { 0.5f, 0.5f, 0.5f },   //
        vec3f { 0.5f, -0.5f, -0.5f }, //

        vec3f { 0.5f, -0.5f, 0.5f },  // BIEN
        vec3f { 0.5f, -0.5f, -0.5f }, //
        vec3f { 0.5f, 0.5f, 0.5f },   //

        vec3f { -0.5f, -0.5f, -0.5f }, // BIEN
        vec3f { 0.5f, -0.5f, -0.5f },  //
        vec3f { 0.5f, -0.5f, 0.5f },   //

        vec3f { 0.5f, -0.5f, 0.5f },   // BIEN
        vec3f { -0.5f, -0.5f, 0.5f },  //
        vec3f { -0.5f, -0.5f, -0.5f }, //

        vec3f { 0.5f, 0.5f, -0.5f },  // BIEN
        vec3f { -0.5f, 0.5f, -0.5f }, //
        vec3f { 0.5f, 0.5f, 0.5f },   //

        vec3f { -0.5f, 0.5f, 0.5f }, // BIEN
        vec3f { 0.5f, 0.5f, 0.5f },  //
        vec3f { -0.5f, 0.5f, -0.5f } //
    };

    vec2f uv[] = {
        vec2f { 1.0f, 0.0f }, //
        vec2f { 0.0f, 0.0f }, //
        vec2f { 1.0f, 1.0f }, //

        vec2f { 0.0f, 1.0f }, //
        vec2f { 1.0f, 1.0f }, //
        vec2f { 0.0f, 0.0f }, //

        vec2f { 0.0f, 0.0f }, //
        vec2f { 1.0f, 0.0f }, //
        vec2f { 1.0f, 1.0f }, //

        vec2f { 1.0f, 1.0f }, //
        vec2f { 0.0f, 1.0f }, //
        vec2f { 0.0f, 0.0f }, //

        vec2f { 1.0f, 0.0f }, //
        vec2f { 1.0f, 1.0f }, //
        vec2f { 0.0f, 1.0f }, //

        vec2f { 0.0f, 1.0f }, //
        vec2f { 0.0f, 0.0f }, //
        vec2f { 1.0f, 0.0f }, //

        vec2f { 1.0f, 1.0f }, //
        vec2f { 1.0f, 0.0f }, //
        vec2f { 0.0f, 1.0f }, //

        vec2f { 0.0f, 0.0f }, //
        vec2f { 0.0f, 1.0f }, //
        vec2f { 1.0f, 0.0f }, //

        vec2f { 0.0f, 1.0f }, //
        vec2f { 1.0f, 1.0f }, //
        vec2f { 1.0f, 0.0f }, //

        vec2f { 1.0f, 0.0f }, //
        vec2f { 0.0f, 0.0f }, //
        vec2f { 0.0f, 1.0f }, //

        vec2f { 1.0f, 1.0f }, //
        vec2f { 0.0f, 1.0f }, //
        vec2f { 1.0f, 0.0f }, //

        vec2f { 0.0f, 0.0f }, //
        vec2f { 1.0f, 0.0f }, //
        vec2f { 0.0f, 1.0f }  //
    };

    vec4f toSendCoords[36];

    Matrix rot           = rotatey(h);
    Matrix rot2          = rotatex(h);
    Matrix rot3          = rotatez(h);
    Matrix perpectiveMat = simpleProjection((float)width / height, 1);
    Matrix viewToWindow  = viewport(0, 0, window.m_width, window.m_height, 255);
    Matrix view          = translate(v1, v2, v3);

    for (int i = 0; i < 36; i++) {
        toSendCoords[i] = viewToWindow * perpectiveMat * (view * rot * rot2 * toHmgcoord(cube[i]));
    }

    window.clearScreen();
    for (int i = 0; i < 12; i++) {
        myGL::triangle(&toSendCoords[i * 3], &window, zbuffer, &uv[i * 3], texture);
    }
    window.show();
}