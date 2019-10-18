#include "Canvas.h"

Canvas::Canvas(short w, short h) : Adafruit_GFX(w, h) {
    short bytes = ((w + 7) / 8) * h;
    if ((buffer = (byte *) malloc(bytes))) {
        for(int i = 0; i < bytes; i++)
            buffer[i] = 0;
//        memset(buffer, 0, bytes);
    }
}

Canvas::~Canvas(void) {
    if (buffer) free(buffer);
}

byte *Canvas::getBuffer(void) {
    return buffer;
}

void Canvas::drawPixel(byte x, byte y, byte color) {
    if ((x < 0) || (x >= width()) || (y < 0) || (y >= height()))
        return;

    // x is which column
    switch (color) {
        case 1:
            buffer[x + (y / 8) * width()] |= (1 << (y & 7));
            break;
        case 0:
            buffer[x + (y / 8) * width()] &= ~(1 << (y & 7));
            break;
        case 2:
            buffer[x + (y / 8) * width()] ^= (1 << (y & 7));
            break;
    }
}

byte Canvas::getPixel(byte x, byte y) {
    return buffer[x + (y / 8) * width()];
}

void Canvas::clear() {
    if(buffer) {
        short bytes = ((WIDTH + 7) / 8) * HEIGHT;
        for(int i = 0; i < bytes; i++)
            buffer[i] = 0;
//        memset(buffer, 0x00, bytes);
    }
}
