#ifndef OLED_H
#define OLED_H

#include <oled/GFX/Canvas.h>
#include <Hardware.h>
#include "OledComm.h"

class Oled {
public:
    Oled(Hardware *hardware, OledComm *comm);

    OledComm *getComm() const;

    void setup();

    void drawBitmap(byte x, byte page, byte widthPx, byte heightPx, const byte *bmp);

    void clearScreen();

    void setFont(const byte newFont[]);

    byte getFontWidth() const;

    void writeString(byte x, byte row, const char *string);

    void bufferString(byte x, const char *string);

    void clear(byte x, byte row, byte widthPx, byte heightRows);

    void setInverted(bool b);

    bool isInverted();

    void drawCanvas(byte x, byte row, byte widthPx, byte heightPx, byte *bytes);

    void drawBufferRow(byte row);

    Canvas *rowBuffer;

private:

    OledComm *comm;
    const byte *font;
    byte fontWidth;
    Hardware* hardware;

    void prepareFullScreenUpdate() const;

    void prepareScreenUpdate(int startX, int endX, int startP, int endP) const;
};


#endif
