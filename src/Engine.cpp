#include <stdio.h>
#include <conio.h>
#include "Engine.h"
#include "World.h"

Engine::Engine(VgaRenderer *vgaRenderer, World *world) {
    this->vgaRenderer = vgaRenderer;
    this->world = world;
    this->playerX = 0;
    this->playerY = 0;
}

void Engine::run() {
    time(&this->lastTime);

    while(true) {
        this->renderFrame();
    }
}

void Engine::renderFrame() {
    updateInputs();

    vector<Actor*> actors = this->world->getActors();
    unsigned int actorsCount = actors.size();

    Actor *currentActor;
    PlanarSprite *actorSprite;
    for (int i = 0; i < actorsCount; ++i) {
        currentActor = actors.at(i);
        actorSprite = currentActor->getPlanarSprite();
        
        vgaRenderer->drawPlanarSprite(currentActor->getX(), currentActor->getY(), actorSprite);
    }

    time_t currentTime;
    time(&currentTime);
    double deltaDime = currentTime - this->lastTime;
    this->lastTime = currentTime;
 
    vgaRenderer->flipPage();
}

void Engine::updateInputs() {
    if (kbhit()) {
        switch (getch())
        {
        case 'd':
            this->playerX += 5;
            break;
        case 'a':
            this->playerX -= 5;
            break;
        case 'w':
            this->playerY -= 5;
            break;
        case 's':
            this->playerY += 5;
            break;
        default:
            break;
        }
    }
    
    Actor *controllableActor = this->world->getControllableActor();
    controllableActor->setX(this->playerX);
    controllableActor->setY(this->playerY);
}
