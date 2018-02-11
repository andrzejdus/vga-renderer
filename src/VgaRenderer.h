#ifndef VGARENDERER_H
#define VGARENDERER_H

#include <inttypes.h>
#include "Sprite.h"
#include "FullscreenSprite.h"
#include "MovableSprite.h"

// TODO clean defines
#define BIOS_VIDEO_INT 0x10
#define BIOS_GET_VIDEO_MODE 0xf
#define BIOS_SET_VIDEO_MODE 0x0
#define VGA_256_COLOR_MODE 0x13
#define VGA_COLORS_COUNT 256
#define VGA_SCREEN_WIDTH 320
#define VGA_SCREEN_HEIGHT 200
#define VGA_SCREEN_BUFFER_SIZE 64000
#define VGA_PLANE_BUFFER_SIZE VGA_SCREEN_BUFFER_SIZE / 4
#define VGA_MEMORY_ADDRESS 0xa0000000
#define VGA_PLANES 4

#define SC_INDEX 0x03c4 /* VGA sequence controller */
#define SC_DATA 0x03c5
#define PALETTE_INDEX 0x03c8 /* VGA digital-to-analog converter */
#define PALETTE_DATA 0x03c9
#define GC_INDEX 0x03ce /* VGA graphics controller */
#define GC_DATA 0x03cf
#define CRTC_INDEX 0x03d4 /* VGA CRT controller */
#define CRTC_DATA 0x03d5
#define VGA_INPUT_STATUS 0x3da

#define MAP_MASK 0x02 /* Sequence controller registers */
#define ALL_PLANES 0xff02
#define MEMORY_MODE 0x04

#define HIGH_ADDRESS 0x0C /* CRT controller registers */
#define LOW_ADDRESS 0x0D
#define UNDERLINE_LOCATION 0x14
#define MODE_CONTROL 0x17

#define DISPLAY_ENABLE 0x01 /* VGA input status bits */
#define VRETRACE 0x08

class VgaRenderer {
public:
    int init();
    void exit();
    void update();
    void drawPixel(int x, int y, uint8_t color);
    void drawMovableSprite(int x, int y, MovableSprite *sprite);
    void drawFullscreenSprite(FullscreenSprite *sprite);
    void setPalette(uint32_t *palette);

private:
    int previousVideoMode;
    uint8_t *vgaScreenBuffer;
    uint16_t visiblePageOffset;
    uint16_t hiddenPageOffset;

    void enter();
    void enableUnchained();
    void leave();
};


#endif //VGARENDERER_H
