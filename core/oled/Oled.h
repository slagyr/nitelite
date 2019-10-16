#ifndef OLED_H
#define OLED_H

#include "OledComm.h"

class Oled {
public:
    Oled(OledComm *comm);

    OledComm *getComm() const;

    void setup();

    void drawBitmap(byte x, byte page, byte widthPx, byte heightPx, const byte *bmp);

    void clearScreen();

    void setFont(const byte font[]);

    byte getFontWidth() const;

    void writeString(byte x, byte row, const char *string);

    void clear(byte x, byte row, byte widthPx, byte heightRows);

    void setInverted(bool b);

    bool isInverted();

    void drawCanvas(byte x, byte row, byte widthPx, byte heightPx, byte *bytes);

private:

    OledComm *comm;
    const byte *font;
    byte fontWidth;

    void prepareFullScreenUpdate() const;

    void prepareScreenUpdate(int startX, int endX, int startP, int endP) const;
};


#endif
