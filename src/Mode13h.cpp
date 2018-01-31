#include "Mode13h.h"
#include <dos.h>
#include <conio.h>
#include <malloc.h>
#include <mem.h>
#include <dos.h>
#include <stdio.h>

static const ScreenDimensions Mode13h::screenDimensions = {320, 200};

int Mode13h::init() {
//	printf("Heap memory, free %lu bytes\n", coreleft());
    printf("Allocating off screen buffer, size %u bytes\n", this->screenSize);

    this->off_screen = (unsigned char *) calloc(this->screenSize, sizeof(char));

//	printf("Heap memory, free %lu bytes\n", coreleft());
    printf("Allocated pointer address %p\n", this->off_screen);
    getchar();

    if (this->off_screen == NULL) {
        return 1;
    }

    this->vga_screen = (unsigned char *) MK_FP(0xa000, 0);
    this->enter();

    return 0;
}

void Mode13h::exit() {
    this->leave();
    free(this->off_screen);
}

void Mode13h::update() {
    while (inp(VGA_INPUT_STATUS) & 8);
    while (!inp(VGA_INPUT_STATUS) & 8);

    memcpy(this->vga_screen, this->off_screen, this->screenSize);
}

void Mode13h::drawPixel(int x, int y, uint8_t color) {
    *(this->off_screen + y * this->screenDimensions.width + x) = color;
}
//
//void Mode13h::drawSprite() {
//
//}

void Mode13h::setPalette(uint32_t *palette) {
    outp(VGA_PALETTE_INDEX, 0);

    for (int i = 0; i < VGA_COLORS_COUNT; i++) {
        outp(VGA_PALETTE_DATA, ((uint8_t ) (palette[i] >> 16)) >> 2);
        outp(VGA_PALETTE_DATA, ((uint8_t ) (palette[i] >> 8)) >> 2);
        outp(VGA_PALETTE_DATA, ((uint8_t ) palette[i]) >> 2);
    }
}

ScreenDimensions Mode13h::getScreenDimensions() {
    return this->screenDimensions;
}

void Mode13h::enter() {
    union REGS in, out;

    in.h.ah = BIOS_GET_VIDEO_MODE;
    int86(BIOS_VIDEO_INT, &in, &out);
    this->old_mode = out.h.al;

    in.h.ah = BIOS_SET_VIDEO_MODE;
    in.h.al = VGA_256_COLOR_MODE;
    int86(BIOS_VIDEO_INT, &in, &out);
}

void Mode13h::leave() {
    union REGS in, out;

    in.h.ah = 0;
    in.h.al = this->old_mode;
    int86(BIOS_VIDEO_INT, &in, &out);
}
