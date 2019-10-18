#ifndef OLED_H
#define OLED_H

#include <oled/GFX/Canvas.h>
#include "OledComm.h"

#define BLACK 0
#define WHITE 1

class Oled : public Canvas {
public:
    Oled(OledComm *comm);

    OledComm *getComm() const;

    void setup();

    void drawBitmap(byte x, byte page, byte widthPx, byte heightPx, const byte *bmp);

    void setFont(const byte font[]);

    byte getFontWidth() const;

    void writeString(byte x, byte row, const char *string);

    void setTextInverted(bool b);

    bool isTextInverted();

    void drawCanvas(byte x, byte row, byte widthPx, byte heightPx, byte *bytes);

    void show();

    void show(int x, int row, int width, int heightPx);

private:

    OledComm *comm;
    const byte *font;
    byte fontWidth;
    bool textInverted;

    void prepareFullScreenUpdate() const;

    void prepareScreenUpdate(int startX, int endX, int startP, int endP) const;
};


#endif
