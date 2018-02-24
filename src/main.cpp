#include <stdio.h>
#include <inttypes.h>
#include <dos.h>
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

int main() {
    Bitmap *testBitmap = loadBitmap("assets/test.bmp");
    Bitmap *gunkBitmap = loadBitmap("assets/gunk2.bmp");
    PlanarSprite *testSprite = loadSprite(testBitmap);
    PlanarSprite *gunkSprite = loadSprite(gunkBitmap);
    getchar();

    VgaRenderer vgaRenderer;

    int virtualWidth = 336;
    int virtualHeight = 200;
    if (vgaRenderer.init(virtualWidth, virtualHeight) != 0) {
        printf("VGA initialization error!\n");
        getchar();
        return 1;
    }

    vgaRenderer.setPalette((uint32_t *) gunkBitmap->getPalette());

    for (unsigned int i = 0; i < 8; i++) {
        for (int y = 0; y < virtualHeight; y++) {
            for (int x = 0; x < virtualWidth; x++) {
                vgaRenderer.drawPixel(x, y, i % 2 + 5);
            }
        }
        vgaRenderer.drawPlanarSprite(0, 0, testSprite);
        vgaRenderer.drawPlanarSprite(219, 132, gunkSprite);
        vgaRenderer.drawPlanarSprite(0, 0, gunkSprite);
        vgaRenderer.drawPlanarSprite(0, 132, gunkSprite);
        vgaRenderer.update(i, 0);
    }
    getchar();

    vgaRenderer.exit();

    return 0;
}
