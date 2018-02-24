#include "VgaRenderer.h"
#include "PlanarSprite.h"
#include <dos.h>
#include <conio.h>
#include <mem.h>

int VgaRenderer::init(uint16_t virtualWidth, uint16_t virtualHeight) {
    this->virtualWidth = virtualWidth;
    this->vgaPlaneBufferSize = virtualWidth / VGA_PLANES * virtualHeight;
    this->vgaScreenBuffer = (uint8_t *) VGA_MEMORY_ADDRESS;
    this->visiblePageOffset = 0;
    this->hiddenPageOffset =  this->vgaPlaneBufferSize;

    this->enter();
    this->enableUnchained();
    outp(CRTC_INDEX, CRTC_OFFSET);
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

    uint16_t highAddress = CRTC_HIGH_ADDRESS | ((visiblePageOffset + offsetX / 4) & 0xff00);
    uint16_t lowAddress  = CRTC_LOW_ADDRESS  | ((visiblePageOffset + offsetX / 4) << 8);

    while ((inp(INPUT_STATUS_1) & INPUT_STATUS_1_DISPLAY_ENABLE));
    outpw(CRTC_INDEX, highAddress);
    outpw(CRTC_INDEX, lowAddress);
    outp(AC_INDEX_AND_DATA, AC_PANNING);
    int o[4];
    o[0] = 0;
    o[1] = 2;
    o[2] = 4;
    o[3] = 6;
    outp(AC_INDEX_AND_DATA, o[offsetX % 4]);
    while (!(inp(INPUT_STATUS_1) & INPUT_STATUS_1_VRETRACE));
}

void VgaRenderer::drawPixel(int x, int y, uint8_t color) {
    int plane = x & (VGA_PLANES - 1);
    outp(SC_INDEX, SC_MAP_MASK);
    outp(SC_DATA, 1 << plane);

    uint16_t drawOffset = hiddenPageOffset + this->virtualWidth / VGA_PLANES * y + x / VGA_PLANES;
    *(this->vgaScreenBuffer + drawOffset) = color;
}

void VgaRenderer::drawPlanarSprite(int x, int y, PlanarSprite *sprite) {
    const uint16_t virtualPlaneWidth = this->virtualWidth / VGA_PLANES;

    for (int plane = 0; plane < VGA_PLANES; plane++) {
        outp(SC_INDEX, SC_MAP_MASK);
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
        outp(SC_INDEX, SC_MAP_MASK);
        outp(SC_DATA, 1 << plane);

        memcpy(this->vgaScreenBuffer + hiddenPageOffset, sprite->getPlaneData(plane), this->vgaPlaneBufferSize);
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
    outp(SC_INDEX, SC_MEMORY_MODE);
    outp(SC_DATA, 0x06);

    outpw(SC_INDEX, SC_ALL_PLANES);

    uint8_t *ptr = (uint8_t *) VGA_MEMORY_ADDRESS;
    for (uint16_t i = 0; i < 0xFFFF; i++) {
        *ptr++ = 0;
    }

    outp(CRTC_INDEX, CRTC_UNDERLINE_LOCATION);
    outp(CRTC_DATA, 0x00);

    outp(CRTC_INDEX, CRTC_MODE_CONTROL);
    outp(CRTC_DATA, 0xe3);
}

void VgaRenderer::leave() {
    union REGS in, out;

    in.h.ah = 0;
    in.h.al = this->previousVideoMode;
    int86(BIOS_VIDEO_INT, &in, &out);
}
