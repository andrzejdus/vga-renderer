#ifndef VGARENDERER_SPRITE_H
#define VGARENDERER_SPRITE_H

#include "Bitmap.h"

class Sprite {
public:
    Sprite(Bitmap *bitmap);

    int getWidth() const;
    int getHeight() const;
    virtual const uint8_t getPixel(int x, int y) const = 0;

private:
    int width;
    int height;
};

#endif //VGARENDERER_SPRITE_H
