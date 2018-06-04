#include <stdio.h>
#include <inttypes.h>
#include <dos.h>
#include <conio.h>
#include "VgaRenderer.h"
#include "BitmapLoader.h"
#include "BmpBitmapInfoPrinter.h"

Bitmap *loadBitmap(char *filename) {
    printf("Loading bitmap data %s\n", filename);
    Bitmap *bitmap = BitmapLoader::load(filename);

    if (bitmap == NULL) {
        printf("Could not load bitmap\n");
        return NULL;
    }

    printf("Done\n");

    if (dynamic_cast<BmpBitmap *>(bitmap)) {
        BmpBitmapInfoPrinter bitmapInfo((BmpBitmap *)bitmap);
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

    return bitmap;
}

PlanarSprite *loadSprite(Bitmap *testBitmap) {
    printf("Converting bitmap to sprite\n");

    PlanarSprite *sprite = new PlanarSprite(testBitmap);
    for (int plane = 0; plane < VGA_PLANES; plane++) {
        printf("Plane width: %d, %d\n", plane, sprite->getPlaneWidth(plane));
    }

    printf("Done\n");

    return sprite;
}

int runTest1(VgaRenderer *vgaRenderer) {
    Bitmap *testBitmap = loadBitmap("assets/test.bmp");
    Bitmap *gunkBitmap = loadBitmap("assets/gunk.bmp");
    if (testBitmap == NULL || gunkBitmap == NULL) {
        return 1;
    }

    PlanarSprite *testSprite = loadSprite(testBitmap);
    PlanarSprite *gunkSprite = loadSprite(gunkBitmap);
    if (testSprite == NULL || gunkSprite == NULL) {
        return 1;
    }

    printf("Press enter to run the test");
    getchar();

    int virtualWidth = 336;
    int virtualHeight = 200;
    if (vgaRenderer->init(virtualWidth, virtualHeight) != 0) {
        printf("VGA initialization error!\n");
        return 1;
    }
    vgaRenderer->setPalette((uint32_t *) gunkBitmap->getPalette());

    unsigned int i = 8;
    while(true) {
        if (kbhit()) {
            char lastKey = getch();

            if (lastKey == 'q') {
                break;
            }

            if (lastKey == 'd' && i < 16) {
                i++;
            }

            if (lastKey == 'a' && i > 0) {
                i--;
            }
        }

        vgaRenderer->drawPlanarSprite(0, 0, testSprite);
        vgaRenderer->drawPlanarSprite(219, 132, gunkSprite);
        vgaRenderer->drawPlanarSprite(0, 0, gunkSprite);
        vgaRenderer->drawPlanarSprite(0, 132, gunkSprite);
        vgaRenderer->drawPixel(virtualWidth / 2, 0, i % 2 + 5);
        vgaRenderer->update(i, 0);
    }

    return 0;
}

int runTest2(VgaRenderer *vgaRenderer) {
    Bitmap *wallX = loadBitmap("assets/wall-x.bmp");
    Bitmap *wallY = loadBitmap("assets/wall-y.bmp");
    if (wallX == NULL || wallY == NULL) {
        return 1;
    }

    PlanarSprite *wallXSprite = loadSprite(wallX);
    PlanarSprite *wallYSprite = loadSprite(wallY);
    if (wallXSprite == NULL || wallYSprite == NULL) {
        return 1;
    }

    int virtualWidth = 320;
    int virtualHeight = 200;
    if (vgaRenderer->init(virtualWidth, virtualHeight) != 0) {
        printf("VGA initialization error!\n");
        return 1;
    }
    vgaRenderer->setPalette((uint32_t *) wallX->getPalette());

    vgaRenderer->drawPlanarSprite(0, 0, wallXSprite);
    vgaRenderer->drawPlanarSprite(20, 0, wallYSprite);
    
    getchar();
    
    return 0;
}

int main() {
    VgaRenderer *vgaRenderer = new VgaRenderer();

    runTest2(vgaRenderer);

    vgaRenderer->exit();

    return 0;
}
