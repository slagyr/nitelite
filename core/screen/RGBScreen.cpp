#include <oled/OledFonts.h>
#include "RGBScreen.h"
#include "Controller.h"
#include "core.h"
#include "string.h"

RGBScreen::RGBScreen() : Screen() {}

const char *RGBScreen::getName() {
    return "RGB";
}

void RGBScreen::enter() {
    Oled *display = Controller::instance->display;
    display->clearScreen();

    display->rowBuffer->clear();
    display->rowBuffer->drawLine(0, 1, 128, 1, WHITE);
    display->drawBufferRow(1);

    update();
}

void RGBScreen::writeColorValue(int row, const char *color, byte colorCol, const char *colorVal) const {
    byte col = 80;
    size_t digits = strlen(colorVal);
    if(digits == 1)
        col = 96;
    else if(digits == 2)
        col = 88;

    Controller::instance->display->rowBuffer->clear();
    Controller::instance->display->bufferString(colorCol, color);
    Controller::instance->display->bufferString(col, colorVal);
    Controller::instance->display->drawBufferRow(row);
}

void RGBScreen::update() {
    Oled *display = Controller::instance->display;
    Canvas *rowBuffer = display->rowBuffer;

    display->setFont(oled_font6x8);
    rowBuffer->clear();
    display->bufferString(1, Controller::instance->mode->getName());
    display->drawBufferRow(0);

    display->setFont(oled_font8x8);
    writeColorValue(2, "RED:", 40, int2str(Controller::instance->red));
    writeColorValue(4, "GREEN:", 24, int2str(Controller::instance->green));
    writeColorValue(6, "BLUE:", 32, int2str(Controller::instance->blue));
}

