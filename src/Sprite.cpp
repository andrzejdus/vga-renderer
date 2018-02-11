#include "Sprite.h"

Sprite::Sprite(Bitmap *bitmap) {
    this->width = bitmap->getWidth();
    this->height = bitmap->getHeight();
}

int Sprite::getWidth() const {
    return this->width;
}

int Sprite::getHeight() const {
    return this->height;
}
