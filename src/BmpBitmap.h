#ifndef VGARENDERER_BMPBITMAP_H
#define VGARENDERER_BMPBITMAP_H

#include <inttypes.h>
#include "Bitmap.h"

struct BmpBitmapFileHeader {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};

struct BmpBitmapInfoHeader {
    uint32_t thisHeaderSize;
    BitmapSize width;
    BitmapSize height;
    uint16_t colorPlanesCount;
    uint16_t bitsPersPixel;
    uint32_t compressionMethod;
    uint32_t rawBitmapDataSize;
    int32_t horizontalPixelsPerMeter;
    int32_t verticalPixelsPerMeter;
    uint32_t colorsCount;
    uint32_t importantColorsCount;
};

class BmpBitmap : public Bitmap {
public:
    BmpBitmap(BmpBitmapFileHeader fileHeader, BmpBitmapInfoHeader infoHeader, BitmapPaletteColor *palette,
              BitmapPixel *pixels);
    virtual BitmapPixel getPixel(int x, int y); // TODO should return address (faster?)?
    virtual BitmapPixel *getPixelsRow(int y);
    virtual BitmapPixel *getPixels();
    virtual BitmapPaletteColor *getPalette();
    virtual BitmapSize getWidth();
    virtual BitmapSize getHeight();
    virtual BitmapSize getSize();
    BmpBitmapFileHeader getFileHeader();
    BmpBitmapInfoHeader getInfoHeader();
private:
    BitmapSize getCalculatedWidth();
    BitmapSize getCalculatedSize();

    BmpBitmapFileHeader fileHeader;
    BmpBitmapInfoHeader infoHeader;
    BitmapPaletteColor *palette;
    BitmapPixel *pixels;
};

#endif //VGARENDERER_BMPBITMAP_H
