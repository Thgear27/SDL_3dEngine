#ifndef __ENGINE3D_H__
#define __ENGINE3D_H__

#include "Window.hpp"
#include "myGL/Texture.hpp"

class myEngine {
private:
    Window window;
    Texture texture;

    float v1 = 0.0f;
    float v2 = 0.0f;
    float v3 = 0.0f;

    const Uint8* keyState = nullptr;
    float* zbuffer;

public:
    myEngine();
    ~myEngine();

    void handleEvents();
    void update();
    void renderAll();
    bool isRunning();
};

#endif // __ENGINE3D_H__