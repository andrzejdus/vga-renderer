#ifndef VGARENDERER_BMPBITMAPINFOPRINTER_H
#define VGARENDERER_BMPBITMAPINFOPRINTER_H

#include "BmpBitmap.h"

class BmpBitmapInfoPrinter {
public:
    BmpBitmapInfoPrinter(BmpBitmap *bitmap);
    void printType();
    void printSize();
    void printOffset();
    void printInfoHeaderSize();
    void printWidth();
    void printHeight();

    void printColorPlanesCount();

    void printBitsPerPixel();
    void printCompressionMethod();
    void printColorsCount();

private:
    BmpBitmap *bitmap;
};

#endif //VGARENDERER_BMPBITMAPINFOPRINTER_H
