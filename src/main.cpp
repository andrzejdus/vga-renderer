#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include "Mode13h.h"

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
    int load(char *fileName) {
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

        this->pixelsData = new uint8_t[pixelsDataSize];

        uint8_t *head = this->pixelsData;
        printf("%u %u\n", sizeof(uint8_t), sizeof(head));
        size_t n = pixelsDataSize;
        while (n > 0) {
            size_t readCount = fread(head, sizeof(uint8_t), n, filePointer);
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

    BitmapFileHeader getFileHeader() {
        return bitmapFileHeader;
    }

    BitmapInfoHeader getInfoHeader() {
        return bitmapInfoHeader;
    }

    uint8_t getPixelColor(int x, int y) {
        return *(this->pixelsData + 64000 - y * bitmapInfoHeader.width -320 + x);
    }

    BitmapPaletteColor *getPalette() {
        return this->paletteData;
    }

private:
    BitmapFileHeader bitmapFileHeader;
    BitmapInfoHeader bitmapInfoHeader;
    BitmapPaletteColor *paletteData;
    uint8_t *pixelsData;
};

class BitmapInfoPrinter {
public:
    BitmapInfoPrinter(Bitmap *bitmap) {
        this->bitmap = bitmap;
    }

    void printType() {
        uint16_t type = this->bitmap->getFileHeader().type;

        printf("Type: %c%c\n", type, *(((char *) &type) + 1));
    }

    void printSize() {
        printf("Size: %u\n", this->bitmap->getFileHeader().size);
    }

    void printOffset() {
        printf("Offset: %u\n", this->bitmap->getFileHeader().offset);
    }

    void printInfoHeaderSize() {
        printf("Info header size: %u\n", this->bitmap->getInfoHeader().thisHeaderSize);
    }

    void printWidth() {
        printf("Width: %u\n", this->bitmap->getInfoHeader().width);
    }

    void printHeight() {
        printf("Height: %u\n", this->bitmap->getInfoHeader().height);
    }

    void printColorPlanesCount() {
        printf("Color planes count: %u\n", this->bitmap->getInfoHeader().colorPlanesCount);
    }

    void printBitsPerPixel() {
        printf("Bits per pixel: %u\n", this->bitmap->getInfoHeader().bitsPersPixel);
    }

    void printCompressionMethod() {
        printf("Compression method: %u\n", this->bitmap->getInfoHeader().compressionMethod);
    }

    void printColorsCount() {
        printf("Colors count: %u\n", this->bitmap->getInfoHeader().colorsCount);
    }

private:
    Bitmap *bitmap;
};

int main() {
    Bitmap bitmap;
    if (bitmap.load("assets/test.bmp") == 0) {
        BitmapInfoPrinter bitmapInfo(&bitmap);
        bitmapInfo.printType();
        bitmapInfo.printSize();
        bitmapInfo.printOffset();
        bitmapInfo.printInfoHeaderSize();
        bitmapInfo.printWidth();
        bitmapInfo.printHeight();
        bitmapInfo.printColorPlanesCount();
        bitmapInfo.printBitsPerPixel();
        bitmapInfo.printCompressionMethod();
        bitmapInfo.printColorsCount();
    }

    Mode13h mode13h;

    if (mode13h.init() == 0) {

        mode13h.setPalette((uint32_t *) bitmap.getPalette());

        for (int x = 0; x < VGA_SCREEN_WIDTH; x++) {
            for (int y = 0; y < VGA_SCREEN_HEIGHT; y++) {
                mode13h.drawPixel(x, y, bitmap.getPixelColor(x, y));
            }
        }

//        for (int x = 0; x < mode13h.getScreenDimensions().width; x++) {
//            for (int y = 0; y < mode13h.getScreenDimensions().height; y++) {
//                mode13h.drawPixel(x, y, y % 256);
//            }
//        }
        mode13h.update();

        printf("OK!\n");
        getchar();

        mode13h.exit();
    } else {
        printf("VGA initialization error!\n");
        getchar();
    }

    return 0;
}
