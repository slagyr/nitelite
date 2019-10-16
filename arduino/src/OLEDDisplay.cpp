#include <avr/pgmspace.h>
#include <Wire.h>
#include <GFX/Canvas.h>
#include <oled/Oled.h>
#include <oled/OledFonts.h>
#include "splash.h"
#include "OLEDDisplay.h"
#include "I2cOledComm.h"

#define BAR_TOP_ROW 2
#define BAR_ROWS 5
#define BAR_WID 12
#define BAR_X_PAD 2
#define BAR_Y_BOT_PAD 1
#define WHITE 1

OLEDDisplay::OLEDDisplay() {
    auto *comm = new I2cOledComm();
    oled = new Oled(comm);
}

void OLEDDisplay::setup() {
    oled->setup();
}

void OLEDDisplay::splash() {
    oled->drawBitmap(0, 0, 128, 64, splashBMP);
}


void OLEDDisplay::showHome() {
    oled->clearScreen();
}

