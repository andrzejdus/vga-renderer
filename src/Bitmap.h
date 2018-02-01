#ifndef MODE13H_BITMAP_H
#define MODE13H_BITMAP_H

#include <inttypes.h>

typedef uint8_t BitmapPixel;
typedef uint32_t BitmapWidth;
typedef uint32_t BitmapHeight;

struct BitmapFileHeader {
    uint16_t type;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offset;
};

struct BitmapInfoHeader {
    uint32_t thisHeaderSize;
    BitmapWidth width;
    BitmapHeight height;
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
    int load(char *fileName); // TODO move to separate class
    BitmapFileHeader getFileHeader();
    BitmapInfoHeader getInfoHeader();
    BitmapPixel getPixelColor(int x, int y); // TODO should return address (faster?)?
    BitmapPixel *getPixelsRow(int y);
    BitmapPaletteColor *getPalette();
    BitmapWidth getWidth();
    BitmapHeight getHeight();
private:
    BitmapFileHeader bitmapFileHeader;
    BitmapInfoHeader bitmapInfoHeader;
    BitmapPaletteColor *paletteData;
    BitmapPixel *pixelsData;
};

#endif //MODE13H_BITMAP_H
