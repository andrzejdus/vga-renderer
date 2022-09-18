#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include "Engine.h"
#include "World.h"

Engine::Engine(VgaRenderer *vgaRenderer, World *world) {
    this->vgaRenderer = vgaRenderer;
    this->world = world;
    this->playerX = 0;
    this->playerY = 0;
    this->speedX = 0;
    this->speedY = 0;
}

void Engine::run() {
    time(&this->lastTime);

    while(true) {
        this->renderFrame();
    }
}

void Engine::renderFrame() {
    time_t currentTime;
    time(&currentTime);
    double deltaTime = currentTime - this->lastTime;
    this->lastTime = currentTime;

    updateInputs(deltaTime);

    vector<Actor*> actors = this->world->getActors();
    unsigned int actorsCount = actors.size();

    Actor *currentActor;
    PlanarSprite *actorSprite;
    for (int i = 0; i < actorsCount; ++i) {
        currentActor = actors.at(i);
        actorSprite = currentActor->getPlanarSprite();
        
        vgaRenderer->drawPlanarSprite(currentActor->getX(), currentActor->getY(), actorSprite);
    }

    vgaRenderer->flipPage();
}

void Engine::updateInputs(double deltaTime) {
    if (kbhit()) {
        switch (getch())
        {
        case 'd':
            this->speedX += 1;
            break;
        case 'a':
            this->speedX -= 1;
            break;
        case 'w':
            this->speedY -= 1;
            break;
        case 's':
            this->speedY += 1;
            break;
        default:
            break;
        }
    }
    
    this->playerX += this->speedX;
    this->playerY += this->speedY;

    Actor *controllableActor = this->world->getControllableActor();
    controllableActor->setX(this->playerX);
    controllableActor->setY(this->playerY);
}
