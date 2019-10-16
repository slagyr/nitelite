#ifndef _ADAFRUIT_GFX_H
#define _ADAFRUIT_GFX_H

#include "Arduino.h"


/// A generic graphics superclass that can handle all sorts of drawing. At a minimum you can subclass and provide drawPixel(). At a maximum you can do a ton of overriding to optimize. Used for any/all Adafruit displays!
class Adafruit_GFX {

public:

    Adafruit_GFX(byte w, byte h); // Constructor

    // This MUST be defined by the subclass:
    virtual void drawPixel(byte x, byte y, byte color) = 0;    ///< Virtual drawPixel() function to draw to the screen/framebuffer/etc, must be overridden in subclass. @param x X coordinate.  @param y Y coordinate. @param color 16-bit pixel color.

    virtual void writeFillRect(byte x, byte y, byte w, byte h, byte color);

    virtual void writeFastVLine(byte x, byte y, byte h, byte color);

    virtual void writeFastHLine(byte x, byte y, byte w, byte color);

    virtual void writeLine(byte x0, byte y0, byte x1, byte y1, byte color);

    // BASIC DRAW API
    // These MAY be overridden by the subclass to provide device-specific
    // optimized code.  Otherwise 'generic' versions are used.

    // It's good to implement those, even if using transaction API
    virtual void drawFastVLine(byte x, byte y, byte h, byte color);

    virtual void drawFastHLine(byte x, byte y, byte w, byte color);

    virtual void fillRect(byte x, byte y, byte w, byte h, byte color);

    virtual void fillScreen(byte color);

    // Optional and probably not necessary to change
    virtual void drawLine(byte x0, byte y0, byte x1, byte y1, byte color);

    virtual void drawRect(byte x, byte y, byte w, byte h, byte color);

    // These exist only with Adafruit_GFX (no subclass overrides)
    void drawCircle(byte x0, byte y0, byte r, byte color);

    void drawCircleHelper(byte x0, byte y0, byte r, byte cornername, byte color);

    void fillCircle(byte x0, byte y0, byte r, byte color);

    void fillCircleHelper(byte x0, byte y0, byte r, byte cornername, byte delta, byte color);

    void drawTriangle(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, byte color);

    void fillTriangle(byte x0, byte y0, byte x1, byte y1, byte x2, byte y2, byte color);

    void drawRoundRect(byte x0, byte y0, byte w, byte h, byte radius, byte color);

    void fillRoundRect(byte x0, byte y0, byte w, byte h, byte radius, byte color);

    byte height() const;

    byte width() const;


protected:
    const byte WIDTH, HEIGHT;
};


#endif
