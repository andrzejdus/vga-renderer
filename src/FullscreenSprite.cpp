#include "FullscreenSprite.h"

FullscreenSprite::FullscreenSprite(Bitmap *bitmap) : Sprite(bitmap) {
    for (int plane = 0; plane < VGA_PLANES; plane++) {
        planeData[plane] = new uint8_t[VGA_PLANE_BUFFER_SIZE];
    }

    for (int y = 0; y < bitmap->getHeight(); y++) {
        for (int x = 0; x < bitmap->getWidth(); x++) {
            int plane = x & (VGA_PLANES - 1);
            *(this->planeData[plane] + (y << 6) + (y << 4) + (x >> 2)) = bitmap->getPixel(x, y);
        }
    }

}

const uint8_t *FullscreenSprite::getPlaneData(int plane) const {
    return this->planeData[plane];
}

const uint8_t FullscreenSprite::getPixel(int x, int y) const {
    int plane = x & (VGA_PLANES - 1);

    return *(this->planeData[plane] + (y << 6) + (y << 4) + (x >> 2));
}

