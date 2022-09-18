#include <stdio.h>
#include <inttypes.h>
#include <dos.h>
#include <conio.h>
#include "VgaRenderer.h"
#include "Engine.h"
#include "BitmapLoader.h"
#include "BmpBitmapInfoPrinter.h"

Bitmap *loadBitmap(char *filename) {
    printf("# Loading bitmap data %s\n", filename);
    BmpBitmap *bmpBitmap = BitmapLoader::load(filename);

    if (bmpBitmap == NULL) {
        printf("Could not load bitmap\n");
        return NULL;
    }

    BmpBitmapInfoPrinter bitmapInfo(bmpBitmap);
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

    printf("Done loading bitmap %s\n", filename);

    return bmpBitmap;
}

PlanarSprite *loadSprite(Bitmap *backgroundBitmap) {
    printf("# Converting bitmap to sprite\n");

    PlanarSprite *sprite = new PlanarSprite(backgroundBitmap);
    for (int plane = 0; plane < VGA_PLANES; plane++) {
        printf("Plane width: %d, %d\n", plane, sprite->getPlaneWidth(plane));
    }

    printf("Done\n");

    return sprite;
}

int loadAssets(World *world) {
    Bitmap *backgroundBitmap = loadBitmap("assets/test.bmp");
    Bitmap *gunkBitmap = loadBitmap("assets/gunk.bmp");
    if (backgroundBitmap == NULL || gunkBitmap == NULL) {
        return 1;
    }

    PlanarSprite *backgroundSprite = loadSprite(backgroundBitmap);
    PlanarSprite *gunkSprite = loadSprite(gunkBitmap);
    if (backgroundSprite == NULL || gunkSprite == NULL) {
        return 1;
    }

    Actor *backgroundActor = new Actor(backgroundSprite);
    Actor *gunkActor = new Actor(gunkSprite);
    world->addActor(backgroundActor);
    world->addActor(gunkActor);
    world->attachToController(gunkActor);

    return 0;
}

int main() {
    World *world = new World();
    if (loadAssets(world) == 1) {
        return 1;
    }

    Bitmap *paletteBitmap = loadBitmap("assets/gunk.bmp");
    VgaRenderer *vgaRenderer = new VgaRenderer((uint32_t *) paletteBitmap->getPalette());
    Engine *engine = new Engine(vgaRenderer, world);
    engine->run();

    vgaRenderer->exit();
    delete vgaRenderer;

    return 0;
}
