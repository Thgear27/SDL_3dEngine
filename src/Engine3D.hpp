#ifndef __ENGINE3D_H__
#define __ENGINE3D_H__

#include "Window.hpp"
#include "EventHandler.hpp"

class Engine3D {
private:
    Window window;
    EventHandler eventHandler;

public:
    Engine3D();
    ~Engine3D();

    void handleEvents();
    void update();
    void renderAll();
    bool isRunning();
};

#endif // __ENGINE3D_H__