#ifndef VGARENDERER_ENGINE_H
#define VGARENDERER_ENGINE_H

#include <time.h>
#include "VgaRenderer.h"
#include "World.h"

class Engine {
public:
    Engine(VgaRenderer *vgaRenderer, World *world);
    void run();
private:
    VgaRenderer *vgaRenderer;
    World *world;
    time_t lastTime;
    int playerX;
    int playerY;

    void renderFrame();
    void updateInputs();
};

#endif //VGARENDERER_ENGINE_H
