#include <memory.h>
#include "MovableSprite.h"

MovableSprite::MovableSprite(Bitmap *bitmap) : Sprite(bitmap) {
    this->data = new uint8_t[bitmap->getSize()];
    for (int y = 0; y < bitmap->getHeight(); ++y) {
        memcpy(this->data + y * bitmap->getWidth(), bitmap->getPixelsRow(y), bitmap->getWidth());
    }
}

const uint8_t *MovableSprite::getData() const {
    return this->data;
}

const uint8_t MovableSprite::getPixel(int x, int y) const {
    return *(this->data + y * this->getWidth() + x);
}
