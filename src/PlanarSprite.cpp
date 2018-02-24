#include "PlanarSprite.h"
#include "stdio.h"

PlanarSprite::PlanarSprite(Bitmap *bitmap) : Sprite(bitmap) {
    // TODO redundant for loops, should be calculated
    for (int plane = 0; plane < VGA_PLANES; plane++) {
        this->planeWidths[plane] = 0;
    }

    for (int y = 0; y < bitmap->getHeight(); y++) {
        for (int x = 0; x < bitmap->getWidth(); x++) {
            int plane = x & (VGA_PLANES - 1);

            this->planeWidths[plane]++;
        }
    }

    for (int plane = 0; plane < VGA_PLANES; plane++) {
        this->planeWidths[plane] /= bitmap->getHeight();
    }

    for (int plane = 0; plane < VGA_PLANES; plane++) {
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
