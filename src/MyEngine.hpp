#ifndef __ENGINE3D_H__
#define __ENGINE3D_H__

#include "Window.hpp"

class myEngine {
private:
    Window window;

    const Uint8* keyState = nullptr;

public:
    myEngine();
    ~myEngine();

    void handleEvents();
    void update();
    void renderAll();
    bool isRunning();
};

#endif // __ENGINE3D_H__