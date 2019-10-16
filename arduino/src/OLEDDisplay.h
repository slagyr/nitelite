#ifndef NITELITE_OLEDDISPLAY_H
#define NITELITE_OLEDDISPLAY_H

#include <Display.h>
#include <oled/Oled.h>
#include "GFX/Canvas.h"

class OLEDDisplay : public Display {
public:
    OLEDDisplay();

    void setup() override;

    void splash() override;

    void showHome() override;

private:

    Oled *oled;
    Canvas *voltageBar;
};


#endif //NITELITE_OLEDDISPLAY_H
