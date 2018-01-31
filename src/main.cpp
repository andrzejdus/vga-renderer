#include <stdio.h>
#include <inttypes.h>
#include "Mode13h.h"
#include "Bitmap.h"

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
