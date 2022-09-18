#include "Actor.h"

Actor::Actor(PlanarSprite *planarSprite, unsigned int initalX, unsigned int initalY) {
    this->planarSprite = planarSprite;
    this->x = initalX;
    this->y = initalY;
}

PlanarSprite* Actor::getPlanarSprite() {
    return this->planarSprite;
}

unsigned int Actor::getX() {
    return x;
}

unsigned int Actor::getY() {
    return y;
}

void Actor::setX(unsigned int value) {
    this->x = value;
}

void Actor::setY(unsigned int value) {
    this->y = value;
}
