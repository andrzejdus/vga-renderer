#ifndef VGARENDERER_BITMAP_H
#define VGARENDERER_BITMAP_H

#include <inttypes.h>

typedef uint8_t BitmapPixel;
typedef uint32_t BitmapSize;

struct BitmapPaletteColor {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reserved;
};

class Bitmap {
public:
    virtual BitmapPixel getPixel(int x, int y) = 0; // TODO should return address (faster?)?
    virtual BitmapPixel *getPixelsRow(int y) = 0;
    virtual BitmapPixel *getPixels() = 0;
    virtual BitmapPaletteColor *getPalette() = 0;
    virtual BitmapSize getWidth() = 0;
    virtual BitmapSize getHeight() = 0;
    virtual BitmapSize getSize() = 0;
};

#endif //VGARENDERER_BITMAP_H
