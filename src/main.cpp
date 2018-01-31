#include <stdio.h>
#include <inttypes.h>
#include "Mode13h.h"
#include "Bitmap.h"
#include "BitmapInfoPrinter.h"

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
