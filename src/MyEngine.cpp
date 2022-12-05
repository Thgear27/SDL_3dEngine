#include "MyEngine.hpp"
#include "myGL/Color.hpp"
#include "myGL/Matrix.hpp"
#include "myGL/Vector.hpp"
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

void line(vec2i p1, vec2i p2, Window* window) {
    bool inverted_plane = false;
    if (std::abs(p2.y - p1.y) > std::abs(p2.x - p1.x)) { // Triangulo con pendiente mayor a 1
        std::swap(p1.x, p1.y);
        std::swap(p2.x, p2.y);
        inverted_plane = true;
    }

    if (p1.x > p2.x) {
        std::swap(p1, p2);
    }

    // Bresenham's algorithm
    int dx  = p2.x - p1.x;
    int dy  = p2.y - p1.y;
    int dxe = std::abs(dy) - std::abs(dx);
    int y   = p1.y; // punto inicial que ira aumentando
    for (int x = p1.x; x <= p2.x; x++) {
        if (!inverted_plane) window->drawPixel(x, y, Color { 1, 1, 1, 1 });
        else window->drawPixel(y, x, Color { 1, 1, 1, 1 });

        dxe += std::abs(dy);

        if (dxe > 0) {
            dxe -= dx;
            y += (p2.y > p1.y) ? 1 : -1;
        }
    }
}

void triangle(vec3f* verts, Window* window) {
    vec2f boxMin = vec2f { (float)window->m_width, (float)window->m_height };
    vec2f boxMax = vec2f { 0, 0 };
    for (int i = 0; i < 3; i++) {
        boxMin.x = std::max(0.0f, std::min(boxMin.x, verts[i].x));
        boxMin.y = std::max(0.0f, std::min(boxMin.y, verts[i].y));

        boxMax.x = std::min((float)window->m_width, std::max(boxMax.x, verts[i].x));
        boxMax.y = std::min((float)window->m_height, std::max(boxMax.y, verts[i].y));
    }

    for (int x = boxMin.x; x < boxMax.x; x++) {
        for (int y = boxMin.y; y < boxMax.y; y++) {
            vec3f bcoord = toBarycentricCoord(verts, vec2f { (float)x, (float)y });
            //    r  g  b  a
            Color color { bcoord.x, bcoord.y, bcoord.z, 1 };
            if (bcoord.x < 0.0f || bcoord.y < 0.0f || bcoord.z < 0.0f) continue;
            window->drawPixel(x, y, color);
        }
    }
}

void myEngine::renderAll() {

    float h = (3.14f * std::sin((float)SDL_GetTicks() / 1000));

    vec3f triangleVerts[] {
        vec3f { 50, 50, 0 },  //
        vec3f { 170, 90, 0 }, //
        vec3f { 50, 130, 0 }  //
    };

    Matrix rot = MatrixIdentity<3>();
    rot[0][0]        = std::cos(h);
    rot[0][1]        = -std::sin(h);
    rot[1][0]        = std::sin(h);
    rot[1][1]        = std::cos(h);
    // rot[0][0] = std::cos (h);
    // rot[0][2] = std::sin (h);
    // rot[2][0] = -std::sin(h);
    // rot[2][2] = std::cos (h);

    Matrix mat = MatrixIdentity<3>();
    mat[0][1]  = h;
    mat[1][0]  = h; 

    

    for (int i = 0; i < 3; i++) {
        triangleVerts[i] = rot * triangleVerts[i];
    }

    window.clearScreen();
    triangle(triangleVerts, &window);
    window.show();
}