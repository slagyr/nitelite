#include <oled/OledFonts.h>
#include "RGBScreen.h"
#include "Controller.h"
#include "common.h"
#include "string.h"

RGBScreen::RGBScreen(Controller *controller) : Screen(controller) {}

const char *RGBScreen::getName() {
    return "RGB";
}

void RGBScreen::enter() {
    Oled *display = controller->display;
    display->clear();
    display->drawLine(0, 9, 128, 9, WHITE);

    controller->display->setFont(oled_font8x8);
    display->writeString(40, 2, "RED:");
    display->writeString(24, 4, "GREEN:");
    display->writeString(32, 6, "BLUE:");

    update();
}

void RGBScreen::writeColorValue(int row, const char *colorVal) const {
    byte col = 80;
    size_t digits = strlen(colorVal);
    if(digits == 1)
        col = 96;
    else if(digits == 2)
        col = 88;
    controller->display->fillRect(80, row * 8, 16, 8, BLACK);
    controller->display->writeString(col, row, colorVal);
}

void RGBScreen::update() {
    controller->display->fillRect(0, 0, 128, 8, BLACK);
    controller->display->setFont(oled_font6x8);
    controller->display->writeString(1, 0, controller->getMode()->getName());

    controller->display->setFont(oled_font8x8);
    writeColorValue(2, int2str(controller->red));
    writeColorValue(4, int2str(controller->green));
    writeColorValue(6, int2str(controller->blue));

    controller->display->show();
}

