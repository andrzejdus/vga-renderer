#ifndef VGARENDERER_FULLSCREENSPRITE_H
#define VGARENDERER_FULLSCREENSPRITE_H

#include "Sprite.h"

#define VGA_PLANES 4

class PlanarSprite : public Sprite {
public:
    PlanarSprite(Bitmap *bitmap);
    virtual const uint8_t getPixel(int x, int y) const;
    const uint8_t *getPlaneData(int plane) const;
    uint16_t getPlaneWidth(int plane);
private:
    uint8_t *planeData[4];
    uint16_t planeWidths[4];
};

#endif //VGARENDERER_FULLSCREENSPRITE_H
