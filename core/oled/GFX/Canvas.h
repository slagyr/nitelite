#ifndef NITELITE_CANVAS_H
#define NITELITE_CANVAS_H

#include "Adafruit_GFX.h"

class Canvas : public Adafruit_GFX {
public:
    Canvas(int16_t w, int16_t h);

    ~Canvas();

    byte *getBuffer();

    void drawPixel(byte x, byte y, byte color) override;

    byte getPixel(byte x, byte y);

    void clear();

protected:
    byte *buffer;
};


#endif
