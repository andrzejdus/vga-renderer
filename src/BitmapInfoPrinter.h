#ifndef MODE13H_BITMAPINFOPRINTER_H
#define MODE13H_BITMAPINFOPRINTER_H

#include "Bitmap.h"

class BitmapInfoPrinter {
public:
    BitmapInfoPrinter(Bitmap *bitmap);
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
    Bitmap *bitmap;
};

#endif //MODE13H_BITMAPINFOPRINTER_H
