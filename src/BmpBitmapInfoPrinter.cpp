#include <inttypes.h>
#include <stdio.h>
#include "BmpBitmapInfoPrinter.h"
#include "BmpBitmap.h"

BmpBitmapInfoPrinter::BmpBitmapInfoPrinter(BmpBitmap *bitmap) {
    this->bitmap = bitmap;
}

void BmpBitmapInfoPrinter::printType() {
    uint16_t type = this->bitmap->getFileHeader().type;

    printf("Type: %c%c\n", type, *(((char *) &type) + 1));
}

void BmpBitmapInfoPrinter::printSize() {
    printf("Size: %u\n", this->bitmap->getFileHeader().size);
}

void BmpBitmapInfoPrinter::printOffset() {
    printf("Offset: %u\n", this->bitmap->getFileHeader().offset);
}

void BmpBitmapInfoPrinter::printInfoHeaderSize() {
    printf("Info header size: %u\n", this->bitmap->getInfoHeader().thisHeaderSize);
}

void BmpBitmapInfoPrinter::printWidth() {
    printf("Width: %u\n", this->bitmap->getInfoHeader().width);
}

void BmpBitmapInfoPrinter::printHeight() {
    printf("Height: %u\n", this->bitmap->getInfoHeader().height);
}

void BmpBitmapInfoPrinter::printColorPlanesCount() {
    printf("Color planes count: %u\n", this->bitmap->getInfoHeader().colorPlanesCount);
}

void BmpBitmapInfoPrinter::printBitsPerPixel() {
    printf("Bits per pixel: %u\n", this->bitmap->getInfoHeader().bitsPersPixel);
}

void BmpBitmapInfoPrinter::printCompressionMethod() {
    printf("Compression method: %u\n", this->bitmap->getInfoHeader().compressionMethod);
}

void BmpBitmapInfoPrinter::printColorsCount() {
    printf("Colors count: %u\n", this->bitmap->getInfoHeader().colorsCount);
}
