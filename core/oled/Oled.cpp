#include "Oled.h"
#include "string.h"
#include "OledFonts.h"
#include <iostream>
using namespace std;

Oled::Oled(OledComm *comm) : Canvas(128, 64) {
    this->comm = comm;
}

OledComm *Oled::getComm() const {
    return comm;
}

void Oled::setup() {
    comm->setup();
    comm->sendCommand(0xAE);        // display off
    comm->sendCommand(0xA6);        // normal display
    comm->sendCommand(0xD5);        // set display clock divide ratio
    comm->sendCommand(0x80);        //  -> suggested ratio 0x80
    comm->sendCommand(0xA8);        // set multiplex ratio
    comm->sendCommand(63);          //  -> height of display
    comm->sendCommand(0xD3);        // set display offset
    comm->sendCommand(0x0);         //  -> none
    comm->sendCommand(0x40|0x0);    // set start line -> 0
    comm->sendCommand(0x8D);        // set charge pump enabled
    comm->sendCommand(0x14);        //  -> 0x14 enable, 0x10 disable
    comm->sendCommand(0x20);        // set memory addressing mode
    comm->sendCommand(0x00);        //  -> 0x00 horizontal, 0x10 page, 0x01 vertical
    comm->sendCommand(0xA1);        // set segment remap (0xA0, 0xA1)
    comm->sendCommand(0xC8);        // set COM output direction (0xC0 inc, 0xC8 dec)
    comm->sendCommand(0xDA);        // set COM pins conf
    comm->sendCommand(0x12);        //  -> got me!?!?!
    comm->sendCommand(0x81);        // set contrast
    comm->sendCommand(0xCF);        //  -> quite high
    comm->sendCommand(0xd9);        // set pre-charge period (in DCLK units)
    comm->sendCommand(0xF1);        //  -> 0xF1 high power, 0x22 battery power
    comm->sendCommand(0xDB);        // set Vcommh deselect level (regulator output)
    comm->sendCommand(0x40);        //  -> (0x40 : 0.89 x Vcc, 0x00 : 0.65 x Vcc)
    comm->sendCommand(0xA4);        // display on (0xA4 from RAM, 0xA5 force ON)
    comm->sendCommand(0x2E);        // deactivate scroll
    comm->sendCommand(0xAF);        // display on
    show();
    setFont(oled_font6x8);
}

void Oled::drawBitmap(byte x, byte page, byte widthPx, byte heightPx, const byte *bmp) {
    int bmpI = 0;
    for(int yp = page; yp < page + heightPx / 8; yp++) {
        for (int xp = x; xp < x + widthPx; xp++) {
            int bufI = yp * width() + xp;
            buffer[bufI] = comm->pmgByte(bmp, bmpI);
        }
    }
}

void Oled::prepareFullScreenUpdate() const {
    prepareScreenUpdate(0, 127, 0, 7);
}

void Oled::prepareScreenUpdate(int startX, int endX, int startP, int endP) const {
    comm->sendCommand(0x21);    // set column address
    comm->sendCommand(startX);  //  -> start at column startX
    comm->sendCommand(endX);    //  -> end at column endX
    comm->sendCommand(0x22);    // set page address
    comm->sendCommand(startP);  //  -> start at page startP
    comm->sendCommand(endP);    //  -> end at page endP
}

void Oled::setFont(const byte *font) {
    this->font = font;
    fontWidth = comm->pmgByte(font, 0);
}

byte Oled::getFontWidth() const {
    return fontWidth;
}

void Oled::writeString(byte x, byte row, const char *msg) {
    byte len = strlen(msg);

    int bufI = row * width() + x;
    for(byte i = 0; i < len; i++) {
        char c = msg[i];
        for( byte j = 0; j < fontWidth; j++) {
            byte col = comm->pmgByte(font, (c - 32) * fontWidth + fontMetaOffset + j);
            buffer[bufI] = textInverted ? ~col : col;
            bufI += 1;
        }
    }
}

void Oled::setTextInverted(bool b) {
    textInverted = b;
}

bool Oled::isTextInverted() {
    return textInverted;
}

void Oled::drawCanvas(byte x, byte row, byte widthPx, byte heightPx, byte *bytes) {
    prepareScreenUpdate(x, x + widthPx - 1, row, row + heightPx / 8 - 1);
    comm->beginTransmission();
    int bytesInScreen = widthPx * heightPx / 8;
    for(int i = 0; i < bytesInScreen; i++) {
        comm->includeByte(bytes[i]);
    }
    comm->endTransmission();
}

void Oled::show() {
    show(0, 0, width(), height());
}

void Oled::show(int x, int page, int widthPx, int heightPx) {
    prepareScreenUpdate(x, x + widthPx - 1, page, page + heightPx / 8 - 1);
    comm->beginTransmission();
    for(int yp = page; yp < page + heightPx / 8; yp++) {
        for (int xp = x; xp < x + widthPx; xp++) {
            int bufI = yp * width() + xp;
            comm->includeByte(buffer[bufI]);
        }
    }
    comm->endTransmission();
}
