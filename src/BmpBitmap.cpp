#include <math.h>
#include "BmpBitmap.h"

BmpBitmap::BmpBitmap(BmpBitmapFileHeader fileHeader, BmpBitmapInfoHeader infoHeader, BitmapPaletteColor *palette,
                     BitmapPixel *pixels) {
    this->fileHeader = fileHeader;
    this->infoHeader = infoHeader;
    this->palette = palette;
    this->pixels = pixels;
}

BitmapPixel BmpBitmap::getPixel(int x, int y) {
    return *(this->pixels + this->getCalculatedSize() - y * this->getCalculatedWidth() - this->getCalculatedWidth() + x);
}

BitmapPixel *BmpBitmap::getPixelsRow(int y) {
    return this->pixels + this->getCalculatedSize() - y * this->getCalculatedWidth() - this->getCalculatedWidth();
}

BitmapPixel *BmpBitmap::getPixels() {
    return this->pixels;
}
BitmapPaletteColor *BmpBitmap::getPalette() {
    return this->palette;
}

BitmapSize BmpBitmap::getWidth() {
    return this->infoHeader.width;
}

BitmapSize BmpBitmap::getHeight() {
    return this->infoHeader.height;
}

BitmapSize BmpBitmap::getSize() {
    return this->getWidth() * this->getHeight();
}

BitmapSize BmpBitmap::getCalculatedWidth() {
    return floor((this->infoHeader.bitsPersPixel * this->infoHeader.width + 31.0) / 32.0) * 4; // TODO get rid of duplicate code
}

BitmapSize BmpBitmap::getCalculatedSize() {
    return this->getCalculatedWidth() * this->getHeight();
}

BmpBitmapFileHeader BmpBitmap::getFileHeader() {
    return this->fileHeader;
}

BmpBitmapInfoHeader BmpBitmap::getInfoHeader() {
    return this->infoHeader;
}
