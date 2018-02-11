#ifndef MODE13H_MOVABLESPRITE_H
#define MODE13H_MOVABLESPRITE_H

#include "Sprite.h"

class MovableSprite : public Sprite {
public:
    MovableSprite(Bitmap *bitmap);
    const uint8_t *getData() const;
    virtual const uint8_t getPixel(int x, int y) const;
private:
    uint8_t *data;
};

#endif //MODE13H_MOVABLESPRITE_H
