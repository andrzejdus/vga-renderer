#include <stdio.h>
#include <math.h>
#include "Bitmap.h"

int Bitmap::load(char *fileName) {
    FILE *filePointer = fopen(fileName, "r");

    if (filePointer == NULL) {
        printf("Couldn't open file\n");

        return 1;
    }

    fread(&this->bitmapFileHeader, sizeof(BitmapFileHeader), 1, filePointer);
    fread(&this->bitmapInfoHeader, sizeof(BitmapInfoHeader), 1, filePointer);

    int realColorsCount =
            this->bitmapInfoHeader.colorsCount > 0 ?
            this->bitmapInfoHeader.colorsCount :
            pow(2, this->bitmapInfoHeader.bitsPersPixel);

    this->paletteData = new BitmapPaletteColor[realColorsCount];
    fread(this->paletteData, sizeof(BitmapPaletteColor), realColorsCount, filePointer);


    int calculatedWidth = floor((this->bitmapInfoHeader.bitsPersPixel * this->bitmapInfoHeader.width + 31.0) / 32.0) * 4;
    size_t pixelsDataSize = calculatedWidth * this->bitmapInfoHeader.height;
    printf("Calculated width: %u\n", calculatedWidth);
    printf("Pixels data size: %u\n", pixelsDataSize);

    this->pixelsData = new BitmapPixel[pixelsDataSize];

    BitmapPixel *head = this->pixelsData;
    printf("%u %u\n", sizeof(uint8_t), sizeof(head));
    size_t n = pixelsDataSize;
    while (n > 0) {
        size_t readCount = fread(head, sizeof(BitmapPixel), n, filePointer);
        n -= readCount;
        head += readCount;

        printf("Read pixels data bytes count: %u, still left: %u\n", readCount, n);

        if (readCount == 0) {
            break;
        }
    }

    fpos_t filePosition;
    fgetpos(filePointer, &filePosition);
    printf("Final file pointer position: %ld\n", filePosition);

    fclose(filePointer);

    if (this->bitmapInfoHeader.thisHeaderSize != 40) {
        printf("Unknown bitmap format, info header size: %u\n", this->bitmapInfoHeader.thisHeaderSize);

        return 1;
    }

    return 0;
}

BitmapFileHeader Bitmap::getFileHeader() {
    return bitmapFileHeader;
}

BitmapInfoHeader Bitmap::getInfoHeader() {
    return bitmapInfoHeader;
}

BitmapPixel Bitmap::getPixelColor(int x, int y) {
    return *(this->pixelsData + 64000 - y * bitmapInfoHeader.width - 320 + x);
}

BitmapPixel *Bitmap::getPixelsRow(int y) {
    return this->pixelsData + 64000 - y * bitmapInfoHeader.width - 320;
}

BitmapPaletteColor *Bitmap::getPalette() {
    return this->paletteData;
}

BitmapWidth Bitmap::getWidth() {
    return this->bitmapInfoHeader.width;
}

BitmapHeight Bitmap::getHeight() {
    return this->bitmapInfoHeader.height;
}
