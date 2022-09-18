#include "BitmapLoader.h"
#include <stdio.h>
#include <math.h>

static BmpBitmap *BitmapLoader::load(char *fileName) {
    FILE *filePointer = fopen(fileName, "r");

    if (filePointer == NULL) {
        printf("Couldn't open file\n");

        return NULL;
    }

    BmpBitmapFileHeader fileHeader;
    BmpBitmapInfoHeader infoHeader;

    fread(&fileHeader, sizeof(BmpBitmapFileHeader), 1, filePointer);
    fread(&infoHeader, sizeof(BmpBitmapInfoHeader), 1, filePointer);

    if (infoHeader.thisHeaderSize != 40) {
        printf("Unknown bitmap format, info header size: %u\n", infoHeader.thisHeaderSize);

        return NULL;
    }

    int realColorsCount =
            infoHeader.colorsCount > 0 ?
            infoHeader.colorsCount :
            pow(2, infoHeader.bitsPersPixel);

    BitmapPaletteColor *paletteData = new BitmapPaletteColor[realColorsCount];
    fread(paletteData, sizeof(BitmapPaletteColor), realColorsCount, filePointer);

    int calculatedWidth = floor((infoHeader.bitsPersPixel * infoHeader.width + 31.0) / 32.0) * 4;
    size_t pixelsDataSize = calculatedWidth * infoHeader.height;
    printf("Calculated width: %u\n", calculatedWidth);
    printf("Pixels data size: %u\n", pixelsDataSize);

    BitmapPixel *pixelsData = new BitmapPixel[pixelsDataSize];

    BitmapPixel *head = pixelsData;
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

    return new BmpBitmap(fileHeader, infoHeader, paletteData, pixelsData);
}
