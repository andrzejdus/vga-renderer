#include <inttypes.h>
#include <stdio.h>
#include "BitmapInfoPrinter.h"
#include "Bitmap.h"

BitmapInfoPrinter::BitmapInfoPrinter(Bitmap *bitmap) {
    this->bitmap = bitmap;
}

void BitmapInfoPrinter::printType() {
    uint16_t type = this->bitmap->getFileHeader().type;

    printf("Type: %c%c\n", type, *(((char *) &type) + 1));
}

void BitmapInfoPrinter::printSize() {
    printf("Size: %u\n", this->bitmap->getFileHeader().size);
}

void BitmapInfoPrinter::printOffset() {
    printf("Offset: %u\n", this->bitmap->getFileHeader().offset);
}

void BitmapInfoPrinter::printInfoHeaderSize() {
    printf("Info header size: %u\n", this->bitmap->getInfoHeader().thisHeaderSize);
}

void BitmapInfoPrinter::printWidth() {
    printf("Width: %u\n", this->bitmap->getInfoHeader().width);
}

void BitmapInfoPrinter::printHeight() {
    printf("Height: %u\n", this->bitmap->getInfoHeader().height);
}

void BitmapInfoPrinter::printColorPlanesCount() {
    printf("Color planes count: %u\n", this->bitmap->getInfoHeader().colorPlanesCount);
}

void BitmapInfoPrinter::printBitsPerPixel() {
    printf("Bits per pixel: %u\n", this->bitmap->getInfoHeader().bitsPersPixel);
}

void BitmapInfoPrinter::printCompressionMethod() {
    printf("Compression method: %u\n", this->bitmap->getInfoHeader().compressionMethod);
}

void BitmapInfoPrinter::printColorsCount() {
    printf("Colors count: %u\n", this->bitmap->getInfoHeader().colorsCount);
}
