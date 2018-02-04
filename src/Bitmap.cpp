#include "Bitmap.h"

Bitmap::Bitmap(BitmapFileHeader fileHeader, BitmapInfoHeader infoHeader, BitmapPaletteColor *palette,
               BitmapPixel *pixels) {
    this->fileHeader = fileHeader;
    this->infoHeader = infoHeader;
    this->palette = palette;
    this->pixels = pixels;
}

BitmapFileHeader Bitmap::getFileHeader() {
    return fileHeader;
}

BitmapInfoHeader Bitmap::getInfoHeader() {
    return infoHeader;
}

BitmapPixel Bitmap::getPixel(int x, int y) {
    return *(this->pixels + 64000 - y * infoHeader.width - 320 + x);
}

BitmapPixel *Bitmap::getPixelsRow(int y) {
    return this->pixels + 64000 - y * infoHeader.width - 320;
}

BitmapPaletteColor *Bitmap::getPalette() {
    return this->palette;
}

BitmapWidth Bitmap::getWidth() {
    return this->infoHeader.width;
}

BitmapHeight Bitmap::getHeight() {
    return this->infoHeader.height;
}
