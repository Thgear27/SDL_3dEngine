#ifndef __ENGINE3D_H__
#define __ENGINE3D_H__

#include "Window.hpp"
#include "EventHandler.hpp"

class myEngine {
private:
    Window window;
    EventHandler eventHandler;

public:
    myEngine();
    ~myEngine();

    void handleEvents();
    void update();
    void renderAll();
    bool isRunning();
};

#endif // __ENGINE3D_H__