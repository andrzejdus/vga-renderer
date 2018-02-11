#ifndef MODE13H_SPRITE_H
#define MODE13H_SPRITE_H


#include "BmpBitmap.h"

#define VGA_PLANES 4
#define VGA_SCREEN_BUFFER_SIZE 64000
#define VGA_PLANE_BUFFER_SIZE VGA_SCREEN_BUFFER_SIZE / 4
#define VGA_SCREEN_WIDTH 320

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


#endif //MODE13H_SPRITE_H
