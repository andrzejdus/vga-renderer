#include "PlanarSprite.h"
#include "stdio.h"

PlanarSprite::PlanarSprite(Bitmap *bitmap) : Sprite(bitmap) {
    for (int plane = 0; plane < VGA_PLANES; plane++) {
        this->planeWidths[plane] = this->getWidth() / VGA_PLANES + (plane < (this->getWidth() % VGA_PLANES) ? 1 : 0);
        this->planeData[plane] = new uint8_t[bitmap->getHeight() * this->getPlaneWidth(plane)];
    }

    for (int y = 0; y < bitmap->getHeight(); y++) {
        for (int x = 0; x < bitmap->getWidth(); x++) {
            int plane = x & (VGA_PLANES - 1);

            *(this->planeData[plane] + this->planeWidths[plane] * y + x / VGA_PLANES) = bitmap->getPixel(x, y);
        }
    }

}

const uint8_t PlanarSprite::getPixel(int x, int y) const {
    int plane = x & (VGA_PLANES - 1);

    return *(this->planeData[plane] + (y << 6) + (y << 4) + (x >> 2)); // TODO code repeat
}

const uint8_t *PlanarSprite::getPlaneData(int plane) const {
    return this->planeData[plane];
}

uint16_t PlanarSprite::getPlaneWidth(int plane) {
    return this->planeWidths[plane];
}
