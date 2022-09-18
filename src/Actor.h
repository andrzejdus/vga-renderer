#ifndef VGARENDERER_ACTOR_H
#define VGARENDERER_ACTOR_H

#include "PlanarSprite.h"

class Actor {
public:
    Actor(PlanarSprite *planarSprite, unsigned int initalX = 0, unsigned int initalY = 0);
    PlanarSprite* getPlanarSprite();
    unsigned int getX();
    unsigned int getY();
    void setX(unsigned int value);
    void setY(unsigned int value);
private:
    PlanarSprite *planarSprite;
    unsigned int x;
    unsigned int y;
};

#endif //VGARENDERER_ACTOR_H
