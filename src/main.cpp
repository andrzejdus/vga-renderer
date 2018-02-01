#include <stdio.h>
#include <inttypes.h>
#include "Mode13h.h"
#include "Bitmap.h"
#include "BitmapInfoPrinter.h"

int main() {
    Bitmap bitmap;
    if (bitmap.load("assets/test.bmp") != 0) {
        printf("Could not load bitmap\n");
        return 1;
    }

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

    Mode13h mode13h;

    if (mode13h.init() != 0) {
        printf("VGA initialization error!\n");
        getchar();
        return 1;
    }

    mode13h.setPalette((uint32_t *) bitmap.getPalette());

    for (int x = 0; x < VGA_SCREEN_WIDTH; x++) {
        for (int y = 0; y < VGA_SCREEN_HEIGHT; y++) {
            mode13h.drawPixel(x, y, bitmap.getPixelColor(x, y));
        }
    }
    mode13h.update();

    printf("Press enter!\n");
    getchar();

    for (int x = 0; x < VGA_SCREEN_WIDTH; x++) {
        for (int y = 0; y < VGA_SCREEN_HEIGHT; y++) {
            mode13h.drawPixel(x, y, 0);
        }
    }
    mode13h.update();

    printf("Press enter!\n");
    getchar();


    mode13h.drawSprite(100, 100, &bitmap);
    mode13h.update();

    printf("Press enter!\n");
    getchar();

    mode13h.exit();

    return 0;
}
