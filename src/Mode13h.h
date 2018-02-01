#ifndef MODE13H_H
#define MODE13H_H

#include <inttypes.h>
#include "Bitmap.h"

#define BIOS_VIDEO_INT 0x10
#define BIOS_GET_VIDEO_MODE 0xf
#define BIOS_SET_VIDEO_MODE 0x0
#define VGA_256_COLOR_MODE 0x13
#define VGA_INPUT_STATUS 0x3da
#define VGA_PALETTE_INDEX 0x03c8
#define VGA_PALETTE_DATA 0x03c9
#define VGA_COLORS_COUNT 256
#define VGA_SCREEN_WIDTH 320
#define VGA_SCREEN_HEIGHT 200
#define VGA_SCREEN_BUFFER_SIZE 64000


class Mode13h {
public:
    int init();
    void exit();
    void update();
    void drawPixel(int x, int y, uint8_t color);
    void drawSprite(int positionX, int positionY, Bitmap *bitmap);
    void setPalette(uint32_t *palette);

private:
    int previousVideoMode;
    unsigned char *vgaScreenBuffer; // TODO use "inttypes.h"
    unsigned char *offScreenBuffer; // TODO use "inttypes.h"

    void enter();
    void leave();
};


#endif //MODE13H_H
