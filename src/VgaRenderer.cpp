#include "VgaRenderer.h"
#include "PlanarSprite.h"
#include <dos.h>
#include <conio.h>
#include <mem.h>

VgaRenderer::VgaRenderer(uint16_t virtualWidth, uint16_t virtualHeight) {
    this->init(virtualWidth, virtualHeight);
}

void VgaRenderer::exit() {
    this->enterPreviousVideoMode();
}

void VgaRenderer::flipPage() {
    uint16_t tempBuffer = this->visiblePageOffset;
    this->visiblePageOffset = this->hiddenPageOffset;
    this->hiddenPageOffset = tempBuffer;

    updateActivePage();
}

void VgaRenderer::updateActivePage() {
    uint16_t highAddress = VGA_CRTC_HIGH_ADDRESS_REGISTER | ((this->visiblePageOffset + this->panOffsetX / 4) & 0xff00);
    uint16_t lowAddress  = VGA_CRTC_LOW_ADDRESS_REGISTER  | ((this->visiblePageOffset + this->panOffsetX / 4) << 8);

    this->waitForDisplayEnable();

    /*
    outpw(VGA_CRTC_INDEX, highAddress);
    equals to
    outp(VGA_CRTC_INDEX, VGA_CRTC_HIGH_ADDRESS_REGISTER);
    outp(VGA_CRTC_DATA, ((visiblePageOffset + offsetX / 4) & 0xff00) >> 8);
    */
    outpw(VGA_CRTC_INDEX, highAddress);
    outpw(VGA_CRTC_INDEX, lowAddress);
    
    outp(VGA_AC_INDEX, VGA_AC_PANNING_REGISTER);
    int o[4];
    o[0] = 0;
    o[1] = 2;
    o[2] = 4;
    o[3] = 6;
    outp(VGA_AC_INDEX, o[this->panOffsetX % 4]);

    this->waitForVretrace();
}

void VgaRenderer::setPanOffset(uint16_t x, uint16_t y) {
    this->panOffsetX = x;
    this->panOffsetY = y;
}

void VgaRenderer::drawPixel(int x, int y, uint8_t color) {
    int plane = x & (VGA_PLANES - 1);
    this->selectPlane(plane);
    uint16_t drawOffset = hiddenPageOffset + this->virtualWidth / VGA_PLANES * y + x / VGA_PLANES;
    *(VGA_MEMORY_ADDRESS + drawOffset) = color;
}

void VgaRenderer::drawPlanarSprite(int x, int y, PlanarSprite *sprite) {
    for (int vgaPlaneIndex = 0; vgaPlaneIndex < VGA_PLANES; vgaPlaneIndex++) {
        int spritePlaneIndex = (vgaPlaneIndex + VGA_PLANES - x % VGA_PLANES) % VGA_PLANES;
        const uint8_t *spritePlaneData = sprite->getPlaneData(spritePlaneIndex);
        const uint16_t spritePlaneWidth = sprite->getPlaneWidth(spritePlaneIndex);
        
        int spriteHeight = sprite->getHeight();

        this->copyToPlane(vgaPlaneIndex, spritePlaneData, spritePlaneWidth, spriteHeight, x, y);
    }
}

void VgaRenderer::copyToPlane(int vgaPlaneIndex, const uint8_t *data, const uint16_t width, int height, int x, int y) {
    this->selectPlane(vgaPlaneIndex); 

    for (int lineNumber = 0; lineNumber < height; lineNumber++) {
        const uint16_t virtualPlaneWidth = this->virtualWidth / VGA_PLANES;
        uint16_t destinationLineOffset = virtualPlaneWidth * (y + lineNumber);
        uint8_t *destinationAddress =
            VGA_MEMORY_ADDRESS +
            hiddenPageOffset +
            destinationLineOffset +
            x / VGA_PLANES +
            (vgaPlaneIndex < (x % VGA_PLANES) ? 1: 0);
        
        uint16_t sourceLineOffset = width * lineNumber;
        const uint8_t *sourceAddress = data + sourceLineOffset;

        memcpy(destinationAddress, sourceAddress, width);
    }
}

void VgaRenderer::drawFullscreenSprite(PlanarSprite *sprite) {
    for (int plane = 0; plane < VGA_PLANES; plane++) {
        this->selectPlane(plane);

        memcpy(VGA_MEMORY_ADDRESS + hiddenPageOffset, sprite->getPlaneData(plane), this->vgaPlaneBufferSize);
    }
}

void VgaRenderer::setPalette(uint32_t *palette) {
    outp(VGA_DAC_PALETTE_INDEX, 0);

    for (int i = 0; i < VGA_COLORS_COUNT; i++) {
        uint8_t red6bit = ((uint8_t ) (palette[i] >> 16)) >> 2;
        uint8_t green6bit = ((uint8_t ) (palette[i] >> 8)) >> 2;
        uint8_t blue6bit = ((uint8_t ) palette[i]) >> 2;

        outp(VGA_DAC_PALETTE_DATA, red6bit);
        outp(VGA_DAC_PALETTE_DATA, green6bit);
        outp(VGA_DAC_PALETTE_DATA, blue6bit);
    }
}

int VgaRenderer::init(uint16_t virtualWidth, uint16_t virtualHeight) {
    this->virtualWidth = virtualWidth;
    this->vgaPlaneBufferSize = virtualWidth / VGA_PLANES * virtualHeight;
    // this->vgaScreenAddress = (uint8_t *) VGA_MEMORY_ADDRESS;
    this->visiblePageOffset = 0;
    this->hiddenPageOffset = this->vgaPlaneBufferSize;
    this->panOffsetX = 0;
    this->panOffsetY = 0;

    this->enterVgaMode13();
    this->enableVgaModeY();
    outp(VGA_CRTC_INDEX, VGA_CRTC_OFFSET_REGISTER);
    outp(VGA_CRTC_DATA, virtualWidth / 8);

    return 0;
}

void VgaRenderer::enterVgaMode13() {
    union REGS in, out;

    in.h.ah = BIOS_GET_VIDEO_MODE;
    int86(BIOS_VIDEO_INT, &in, &out);
    this->previousVideoMode = out.h.al;

    in.h.ah = BIOS_SET_VIDEO_MODE;
    in.h.al = VGA_256_COLOR_MODE_13;
    int86(BIOS_VIDEO_INT, &in, &out);
}

void VgaRenderer::enableVgaModeY() {
    this->disableChain4();
    this->disableDoubleWordMode();
    this->disableWordMode();
    this->clearVgaMemory();
}

void VgaRenderer::enterPreviousVideoMode() {
    union REGS in, out;

    in.h.ah = 0;
    in.h.al = this->previousVideoMode;
    int86(BIOS_VIDEO_INT, &in, &out);
}

void VgaRenderer::disableChain4() {
    outp(VGA_SC_INDEX, VGA_SC_MEMORY_MODE_REGISTER);
    outp(VGA_SC_DATA, 0x06);
}

void VgaRenderer::disableDoubleWordMode() {
    outp(VGA_CRTC_INDEX, VGA_CRTC_UNDERLINE_LOCATION_REGISTER);
    outp(VGA_CRTC_DATA, 0x00);
}

void VgaRenderer::disableWordMode() {
    outp(VGA_CRTC_INDEX, VGA_CRTC_MODE_CONTROL_REGISTER);
    outp(VGA_CRTC_DATA, 0xe3);
}

void VgaRenderer::selectAllPlanes() {
    outp(VGA_SC_INDEX, VGA_SC_MAP_MASK_REGISTER);
    outp(VGA_SC_DATA, VGA_SC_ALL_PLANES);
}

void VgaRenderer::selectPlane(int plane) {
    outp(VGA_SC_INDEX, VGA_SC_MAP_MASK_REGISTER);
    outp(VGA_SC_DATA, 1 << plane);
}

void VgaRenderer::clearVgaMemory() {
    this->selectAllPlanes();

    uint8_t *ptr = (uint8_t *) VGA_MEMORY_ADDRESS;
    for (uint16_t i = 0; i < 0xFFFF; i++) {
        *ptr++ = 0;
    }
}
void VgaRenderer::waitForDisplayEnable() {
    while ((inp(VGA_INPUT_STATUS_1) & VGA_INPUT_STATUS_1_DISPLAY_ENABLE));
}

void VgaRenderer::waitForVretrace() {
    while (!(inp(VGA_INPUT_STATUS_1) & VGA_INPUT_STATUS_1_VRETRACE));
}