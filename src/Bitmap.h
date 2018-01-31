#ifndef MODE13H_BITMAP_H
#define MODE13H_BITMAP_H

#include <inttypes.h>

struct BitmapFileHeader {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};

struct BitmapInfoHeader {
    uint32_t thisHeaderSize;
    int32_t width;
    int32_t height;
    uint16_t colorPlanesCount;
    uint16_t bitsPersPixel;
    uint32_t compressionMethod;
    uint32_t rawBitmapDataSize;
    int32_t horizontalPixelsPerMeter;
    int32_t verticalPixelsPerMeter;
    uint32_t colorsCount;
    uint32_t importantColorsCount;
};

struct BitmapPaletteColor {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t reserved;
};

class Bitmap {
public:
    int load(char *fileName);
    BitmapFileHeader getFileHeader();
    BitmapInfoHeader getInfoHeader();
    uint8_t getPixelColor(int x, int y);
    BitmapPaletteColor *getPalette();

private:
    BitmapFileHeader bitmapFileHeader;
    BitmapInfoHeader bitmapInfoHeader;
    BitmapPaletteColor *paletteData;
    uint8_t *pixelsData;
};

#endif //MODE13H_BITMAP_H
