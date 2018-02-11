#include "Mode13h.h"
#include "FullscreenSprite.h"
#include "MovableSprite.h"
#include <dos.h>
#include <conio.h>
#include <mem.h>

int Mode13h::init() {
    this->vgaScreenBuffer = (uint8_t *) 0xa0000000;
    this->visiblePageOffset = 0;
    this->hiddenPageOffset = VGA_PLANE_BUFFER_SIZE;

    this->enter();
    this->enableUnchained();

    return 0;
}

void Mode13h::exit() {
    this->leave();
}

void Mode13h::update() {
    uint16_t tempBuffer = this->visiblePageOffset;
    this->visiblePageOffset = this->hiddenPageOffset;
    this->hiddenPageOffset = tempBuffer;

    uint16_t highAddress = HIGH_ADDRESS | (visiblePageOffset & 0xff00);
    uint16_t lowAddress  = LOW_ADDRESS  | (visiblePageOffset << 8);

    while ((inp(VGA_INPUT_STATUS) & DISPLAY_ENABLE));
    outpw(CRTC_INDEX, highAddress);
    outpw(CRTC_INDEX, lowAddress);
    while (!(inp(VGA_INPUT_STATUS) & VRETRACE));
}

void Mode13h::drawPixel(int x, int y, uint8_t color) {
    int plane = x & 3;
    outp(SC_INDEX, MAP_MASK);
    outp(SC_DATA, 1 << plane);

    *(this->vgaScreenBuffer + hiddenPageOffset + (y << 6) + (y << 4) + (x >> 2)) = color;
}

void Mode13h::drawMovableSprite(int offsetX, int offsetY, MovableSprite *sprite) {
    for (int y = 0; y < sprite->getHeight(); y++) {
        for (int x = 0; x < sprite->getWidth(); x++) {
            this->drawPixel(offsetX + x, offsetY + y, sprite->getPixel(x, y));
        }
    }
}

void Mode13h::drawFullscreenSprite(FullscreenSprite *sprite) {
    for (int plane = 0; plane < VGA_PLANES; plane++) {
        outp(SC_INDEX, MAP_MASK);
        outp(SC_DATA, 1 << plane);

        memcpy(this->vgaScreenBuffer + hiddenPageOffset, sprite->getPlaneData(plane),
               VGA_PLANE_BUFFER_SIZE);
    }
}

void Mode13h::setPalette(uint32_t *palette) {
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

void Mode13h::enter() {
    union REGS in, out;

    in.h.ah = BIOS_GET_VIDEO_MODE;
    int86(BIOS_VIDEO_INT, &in, &out);
    this->previousVideoMode = out.h.al;

    in.h.ah = BIOS_SET_VIDEO_MODE;
    in.h.al = VGA_256_COLOR_MODE;
    int86(BIOS_VIDEO_INT, &in, &out);
}

void Mode13h::enableUnchained() {
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

void Mode13h::leave() {
    union REGS in, out;

    in.h.ah = 0;
    in.h.al = this->previousVideoMode;
    int86(BIOS_VIDEO_INT, &in, &out);
}
