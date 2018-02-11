#include <stdio.h>
#include <inttypes.h>
#include "VgaRenderer.h"
#include "BitmapLoader.h"
#include "BmpBitmapInfoPrinter.h"

int main() {
    printf("Loading bitmap data\n");
    Bitmap *testBitmap = BitmapLoader::load("assets/test.bmp");
    Bitmap *gunkBitmap = BitmapLoader::load("assets/The_Gunk.bmp");
    if (testBitmap == NULL || gunkBitmap == NULL) {
        printf("Could not load bitmap\n");
        return 1;
    } else {
        printf("Done\n");
    }
    printf("Gunk size: %d, %d\n", gunkBitmap->getWidth(), gunkBitmap->getHeight());

    printf("Converting bitmap to sprite\n");
    FullscreenSprite testSprite(testBitmap);
    MovableSprite gunkSprite(gunkBitmap);
    printf("Done\n");

    if (dynamic_cast<BmpBitmap *>(testBitmap)) {
        BmpBitmapInfoPrinter bitmapInfo((BmpBitmap *)testBitmap);
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

    VgaRenderer vgaRenderer;

    if (vgaRenderer.init() != 0) {
        printf("VGA initialization error!\n");
        getchar();
        return 1;
    }

    vgaRenderer.setPalette((uint32_t *) testBitmap->getPalette());

//    for (int y = 0; y < gunkBitmap->getHeight(); y++) {
//        for (int x = 0; x < gunkBitmap->getWidth(); x++) {
//            mode13h.drawPixel(x, y, gunkBitmap->getPixel(x, y));
//        }
//    }
//    mode13h.update();
//
//    getchar();
//
//    for (int x = 0; x < VGA_SCREEN_WIDTH; x++) {
//        for (int y = 0; y < VGA_SCREEN_HEIGHT; y++) {
//            mode13h.drawPixel(x, y, 0);
//        }
//    }
//    mode13h.update();
//
//    getchar();

    vgaRenderer.drawFullscreenSprite(&testSprite);
    vgaRenderer.update();

    getchar();

    vgaRenderer.drawMovableSprite(10, 10, &gunkSprite);
    vgaRenderer.update();

    getchar();

    vgaRenderer.exit();

    return 0;
}
