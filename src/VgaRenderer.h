#ifndef VGARENDERER_H
#define VGARENDERER_H

#include <inttypes.h>
#include "Sprite.h"
#include "PlanarSprite.h"

// TODO clean defines
#define BIOS_VIDEO_INT 0x10
#define BIOS_GET_VIDEO_MODE 0xf
#define BIOS_SET_VIDEO_MODE 0x0
#define VGA_256_COLOR_MODE 0x13
#define VGA_COLORS_COUNT 256
#define VGA_MEMORY_ADDRESS 0xa0000000
#define VGA_PLANES 4

/* VGA DAC palette controller */
#define PALETTE_INDEX 0x03c8
#define PALETTE_DATA 0x03c9

/* VGA sequence controller */
#define SC_INDEX 0x03c4
#define SC_DATA 0x03c5
/* Sequence controller registers */
#define SC_MAP_MASK 0x02
#define SC_ALL_PLANES 0xff02
#define SC_MEMORY_MODE 0x04

/* CRT controller */
#define CRTC_INDEX 0x03d4
#define CRTC_DATA 0x03d5
/* CRT controller registers */
#define CRTC_OFFSET 0x13
#define CRTC_HIGH_ADDRESS 0x0C
#define CRTC_LOW_ADDRESS 0x0D
#define CRTC_UNDERLINE_LOCATION 0x14
#define CRTC_MODE_CONTROL 0x17

/* Attribute controller */
#define AC_INDEX_AND_DATA 0x03c0
/* Attribute controller registers */
#define AC_PANNING 0x13

/* VGA input status 1 */
#define INPUT_STATUS_1 0x3da
/* VGA input status 1 bits */
#define INPUT_STATUS_1_DISPLAY_ENABLE 0x01
#define INPUT_STATUS_1_VRETRACE 0x08

class VgaRenderer {
public:
    int init(uint16_t virtualWidth = 320, uint16_t virtualHeight = 200);
    void exit();
    void update(uint16_t offsetX = 0, uint16_t offsetY = 0);
    void drawPixel(int x, int y, uint8_t color);
    void drawPlanarSprite(int x, int y, PlanarSprite *sprite);
    void drawFullscreenSprite(PlanarSprite *sprite);
    void setPalette(uint32_t *palette);
private:
    uint16_t virtualWidth;
    uint16_t vgaPlaneBufferSize;
    uint8_t *vgaScreenBuffer;
    uint16_t visiblePageOffset;
    uint16_t hiddenPageOffset;
    int previousVideoMode;

    void enter();
    void enableUnchained();
    void leave();
};

#endif //VGARENDERER_H
