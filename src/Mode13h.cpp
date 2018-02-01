#include "Mode13h.h"
#include <dos.h>
#include <conio.h>
#include <malloc.h>
#include <mem.h>
#include <dos.h>
#include <stdio.h>

int Mode13h::init() {
//	printf("Heap memory, free %lu bytes\n", coreleft());
    printf("Allocating off screen buffer, size %u bytes\n", VGA_SCREEN_BUFFER_SIZE);

    this->offScreenBuffer = (unsigned char *) calloc(VGA_SCREEN_BUFFER_SIZE, sizeof(char));

//	printf("Heap memory, free %lu bytes\n", coreleft());
    printf("Allocated pointer address %p\n", this->offScreenBuffer);
    getchar();

    if (this->offScreenBuffer == NULL) {
        return 1;
    }

    this->vgaScreenBuffer = (unsigned char *) MK_FP(0xa000, 0);
    this->enter();

    return 0;
}

void Mode13h::exit() {
    this->leave();
    free(this->offScreenBuffer);
}

void Mode13h::update() {
    while (inp(VGA_INPUT_STATUS) & 8);
    while (!inp(VGA_INPUT_STATUS) & 8);

    memcpy(this->vgaScreenBuffer, this->offScreenBuffer, VGA_SCREEN_BUFFER_SIZE);
}

void Mode13h::drawPixel(int x, int y, uint8_t color) {
    *(this->offScreenBuffer + y * VGA_SCREEN_WIDTH + x) = color;
}

void Mode13h::drawSprite(int positionX, int positionY, Bitmap *bitmap) {
    for (int y = 0; y < bitmap->getHeight() && y < VGA_SCREEN_HEIGHT; y++) {
        memcpy(this->offScreenBuffer + (positionY + y) * VGA_SCREEN_WIDTH + positionX,
               bitmap->getPixelsRow(y),
               bitmap->getWidth());
    }
}

void Mode13h::setPalette(uint32_t *palette) {
    outp(VGA_PALETTE_INDEX, 0);

    for (int i = 0; i < VGA_COLORS_COUNT; i++) {
        uint8_t red6bit = ((uint8_t ) (palette[i] >> 16)) >> 2;
        uint8_t green6bit = ((uint8_t ) (palette[i] >> 8)) >> 2;
        uint8_t blue6bit = ((uint8_t ) palette[i]) >> 2;

        outp(VGA_PALETTE_DATA, red6bit);
        outp(VGA_PALETTE_DATA, green6bit);
        outp(VGA_PALETTE_DATA, blue6bit);
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

void Mode13h::leave() {
    union REGS in, out;

    in.h.ah = 0;
    in.h.al = this->previousVideoMode;
    int86(BIOS_VIDEO_INT, &in, &out);
}
