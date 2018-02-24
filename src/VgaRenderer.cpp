#include "VgaRenderer.h"
#include "PlanarSprite.h"
#include <dos.h>
#include <conio.h>
#include <mem.h>

int VgaRenderer::init(uint16_t virtualWidth, uint16_t virtualHeight) {
    this->virtualWidth = virtualWidth;
    this->vgaBufferSize = virtualWidth / 4 * virtualHeight;
    this->vgaScreenBuffer = (uint8_t *) 0xa0000000;
    this->visiblePageOffset = 0;
    this->hiddenPageOffset =  this->vgaBufferSize;

    this->enter();
    this->enableUnchained();
    outp(CRTC_INDEX, 0x13);
    outp(CRTC_DATA, virtualWidth / 8);

    return 0;
}

void VgaRenderer::exit() {
    this->leave();
}

void VgaRenderer::update(uint16_t offsetX, uint16_t offsetY) {
    uint16_t tempBuffer = this->visiblePageOffset;
    this->visiblePageOffset = this->hiddenPageOffset;
    this->hiddenPageOffset = tempBuffer;

    uint16_t highAddress = HIGH_ADDRESS | ((visiblePageOffset + offsetX / 4) & 0xff00);
    uint16_t lowAddress  = LOW_ADDRESS  | ((visiblePageOffset + offsetX / 4) << 8);

    while ((inp(VGA_INPUT_STATUS) & DISPLAY_ENABLE));
    outpw(CRTC_INDEX, highAddress);
    outpw(CRTC_INDEX, lowAddress);
    outp(0x03c0, 0x13);
    int o[4];
    o[0] = 0;
    o[1] = 2;
    o[2] = 4;
    o[3] = 6;
    outp(0x03c0, o[offsetX % 4]);
    while (!(inp(VGA_INPUT_STATUS) & VRETRACE));
}

void VgaRenderer::drawPixel(int x, int y, uint8_t color) {
    int plane = x & (VGA_PLANES - 1);
    outp(SC_INDEX, MAP_MASK);
    outp(SC_DATA, 1 << plane);

    uint16_t drawOffset = hiddenPageOffset + this->virtualWidth / VGA_PLANES * y + x / VGA_PLANES;
    *(this->vgaScreenBuffer + drawOffset) = color;
}

void VgaRenderer::drawPlanarSprite(int x, int y, PlanarSprite *sprite) {
    const uint16_t virtualPlaneWidth = this->virtualWidth / VGA_PLANES;

    for (int plane = 0; plane < VGA_PLANES; plane++) {
        outp(SC_INDEX, MAP_MASK);
        outp(SC_DATA, 1 << plane);

        const uint8_t *spritePlaneData = sprite->getPlaneData(plane);
        const uint16_t spritePlaneWidth = sprite->getPlaneWidth(plane);

        for (int line = 0; line < sprite->getHeight(); line++) {
            memcpy(this->vgaScreenBuffer + hiddenPageOffset + virtualPlaneWidth * (y + line) + x / VGA_PLANES,
                   spritePlaneData + spritePlaneWidth * line,
                   spritePlaneWidth);
        }
    }
}

void VgaRenderer::drawFullscreenSprite(PlanarSprite *sprite) {
    for (int plane = 0; plane < VGA_PLANES; plane++) {
        outp(SC_INDEX, MAP_MASK);
        outp(SC_DATA, 1 << plane);

        memcpy(this->vgaScreenBuffer + hiddenPageOffset, sprite->getPlaneData(plane),
               VGA_PLANE_BUFFER_SIZE);
    }
}

void VgaRenderer::setPalette(uint32_t *palette) {
    outp(PALETTE_INDEX, 0);

    for (int i = 0; i < VGA_COLORS_COUNT; i++) {
        uint8_t red6bit = ((uint8_t ) (palette[i] >> 16)) >> 2;
        uint8_t green6bit = ((uint8_t ) (palette[i] >> 8)) >> 2;
        uint8_t blue6bit = ((uint8_t ) palette[i]) >> 2;

        outp(PALETTE_DATA, red6bit);
        outp(PALETTE_DATA, green6bit);
        outp(PALETTE_DATA, blue6bit);
    }
}

void VgaRenderer::enter() {
    union REGS in, out;

    in.h.ah = BIOS_GET_VIDEO_MODE;
    int86(BIOS_VIDEO_INT, &in, &out);
    this->previousVideoMode = out.h.al;

    in.h.ah = BIOS_SET_VIDEO_MODE;
    in.h.al = VGA_256_COLOR_MODE;
    int86(BIOS_VIDEO_INT, &in, &out);
}

void VgaRenderer::enableUnchained() {
    outp(SC_INDEX, MEMORY_MODE);
    outp(SC_DATA, 0x06);

    outpw(SC_INDEX, ALL_PLANES);

    uint8_t *ptr = (uint8_t *) 0xa0000000;
    for (uint16_t i = 0; i < 0xFFFF; i++) {
        *ptr++ = 0;
    }

    outp(CRTC_INDEX, UNDERLINE_LOCATION);
    outp(CRTC_DATA, 0x00);

    outp(CRTC_INDEX, MODE_CONTROL);
    outp(CRTC_DATA, 0xe3);
}

void VgaRenderer::leave() {
    union REGS in, out;

    in.h.ah = 0;
    in.h.al = this->previousVideoMode;
    int86(BIOS_VIDEO_INT, &in, &out);
}
