#ifndef VGARENDERER_H
#define VGARENDERER_H

#include <inttypes.h>
#include "Sprite.h"
#include "PlanarSprite.h"

// TODO clean defines
#define BIOS_VIDEO_INT 0x10
#define BIOS_GET_VIDEO_MODE 0xf
#define BIOS_SET_VIDEO_MODE 0x0

/* VGA General */
#define VGA_MEMORY_ADDRESS (uint8_t *) 0xa0000000
#define VGA_256_COLOR_MODE_13 0x13
#define VGA_COLORS_COUNT 256
#define VGA_PLANES 4

/* VGA DAC Palette Controller */
#define VGA_DAC_PALETTE_INDEX 0x03c8
#define VGA_DAC_PALETTE_DATA 0x03c9

/* VGA Sequence Controller */
#define VGA_SC_INDEX 0x03c4
#define VGA_SC_DATA 0x03c5
/* VGA Sequence Controller registers */
#define VGA_SC_MAP_MASK_REGISTER 0x02
#define VGA_SC_MEMORY_MODE_REGISTER 0x04
/* VGA Sequence Controller values */
#define VGA_SC_ALL_PLANES 0xff

/* CRT Controller */
#define VGA_CRTC_INDEX 0x03d4
#define VGA_CRTC_DATA 0x03d5
/* CRT Controller registers */
#define VGA_CRTC_OFFSET_REGISTER 0x13
#define VGA_CRTC_UNDERLINE_LOCATION_REGISTER 0x14
#define VGA_CRTC_MODE_CONTROL_REGISTER 0x17
#define VGA_CRTC_HIGH_ADDRESS_REGISTER 0x0C
#define VGA_CRTC_LOW_ADDRESS_REGISTER 0x0D

/* Attribute Controller */
#define VGA_AC_INDEX 0x03c0
/* Attribute Controller registers */
#define VGA_AC_PANNING_REGISTER 0x13

/* VGA input status 1 */
#define VGA_INPUT_STATUS_1 0x3da
/* VGA input status 1 bits */
#define VGA_INPUT_STATUS_1_DISPLAY_ENABLE 0x01
#define VGA_INPUT_STATUS_1_VRETRACE 0x08

class VgaRenderer {
public:
    VgaRenderer(uint32_t *palette, uint16_t virtualWidth = 320, uint16_t virtualHeight = 200);
    void exit();

    void flipPage();
    void updateActivePage();
    void setPanOffset(uint16_t offsetX, uint16_t offsetY);

    void drawPixel(int x, int y, uint8_t color);
    void drawPlanarSprite(int x, int y, PlanarSprite *sprite);
    void drawFullscreenSprite(PlanarSprite *sprite);
    
    void setPalette(uint32_t *palette);
private:
    uint16_t virtualWidth;
    uint16_t vgaPlaneBufferSize;
    uint16_t visiblePageOffset;
    uint16_t hiddenPageOffset;
    uint16_t panOffsetX;
    uint16_t panOffsetY;
    int previousVideoMode;

    int init(uint16_t virtualWidth, uint16_t virtualHeight);

    void enterVgaMode13();
    void enableVgaModeY();
    void enterPreviousVideoMode();

    void clearVgaMemory();
    void disableChain4();
    void disableDoubleWordMode();
    void disableWordMode();
    void selectAllPlanes();
    void selectPlane(int plane);
    void waitForDisplayEnable();
    void waitForVretrace();
};

#endif //VGARENDERER_H
