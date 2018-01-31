#ifndef DEV_MODE13H_H
#define DEV_MODE13H_H

#include <inttypes.h>
#include "ScreenDimensions.h"

#define BIOS_VIDEO_INT 0x10
#define BIOS_GET_VIDEO_MODE 0xf
#define BIOS_SET_VIDEO_MODE 0x0
#define VGA_256_COLOR_MODE 0x13
#define VGA_INPUT_STATUS 0x3da
#define VGA_COLORS_COUNT 256
#define VGA_PALETTE_INDEX 0x03c8
#define VGA_PALETTE_DATA 0x03c9

class Mode13h {
public:
    int init();
    void exit();
    void update();
    void drawPixel(int x, int y, uint8_t color);
    void setPalette(uint32_t *palette);
    ScreenDimensions getScreenDimensions();

private:
    static const unsigned int vgaInputStatus = VGA_INPUT_STATUS;
    static const unsigned int screenSize = 64000;
    static const ScreenDimensions screenDimensions;

    int old_mode;
    unsigned char *vga_screen;
    unsigned char *off_screen;

    void enter();
    void leave();
};


#endif //DEV_MODE13H_H
