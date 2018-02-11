#ifndef MODE13H_FULLSCREENSPRITE_H
#define MODE13H_FULLSCREENSPRITE_H


#include "Sprite.h"

class FullscreenSprite : public Sprite {
public:
    FullscreenSprite(Bitmap *bitmap);
    const uint8_t *getPlaneData(int plane) const;
    virtual const uint8_t getPixel(int x, int y) const;
private:
    uint8_t *planeData[4];
};


#endif //MODE13H_FULLSCREENSPRITE_H
