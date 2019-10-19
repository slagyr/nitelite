#ifndef NITELITE_CANVAS_H
#define NITELITE_CANVAS_H

#include "Adafruit_GFX.h"

#define WHITE 1
#define BLACK 0

class Canvas : public Adafruit_GFX {
public:
    Canvas(short w, short h);

    ~Canvas();

    byte *getBuffer();

    void drawPixel(byte x, byte y, byte color) override;

    byte getPixel(byte x, byte y);

    void clear();

protected:
    byte *buffer;
};


#endif
