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
    double playerX;
    double playerY;
    double speedX;
    double speedY;

    void renderFrame();
    void updateInputs(double deltaTime);
};

#endif //VGARENDERER_ENGINE_H
