#include <oled/OledFonts.h>
#include "SettingsScreen.h"
#include "Controller.h"
#include "core.h"
#include "string.h"

SettingsScreen::SettingsScreen() : Screen() {}

const char *SettingsScreen::getName() {
    return "Settings";
}

void SettingsScreen::enter() {
    Oled *display = Controller::instance->display;
    display->clearScreen();

    display->rowBuffer->clear();
    display->rowBuffer->drawLine(0, 1, 128, 1, WHITE);
    display->drawCanvas(0, 1, 128, 8, display->rowBuffer->getBuffer());

    display->setFont(oled_font6x8);
    display->writeString(1, 0, "Settings");

    update();
}

void SettingsScreen::update() {
    Oled *display = Controller::instance->display;
    Canvas *rowBuffer = display->rowBuffer;

    display->setFont(oled_font6x8);

    rowBuffer->clear();
    display->bufferString(0, "Screen Timeout Secs:");
    display->drawBufferRow(2);

    rowBuffer->clear();
    display->bufferString(0, "(Red knob):");
    byte sTimeout = Controller::instance->screenTimeout();
    if(sTimeout > SCREEN_TIMEOUT_MAX)
        display->bufferString(96, "Never");
    else
        display->bufferString(108, int2str(sTimeout));
    display->drawBufferRow(3);

    rowBuffer->clear();
    display->bufferString(0, "Lights Timeout Mins:");
    display->drawBufferRow(5);

    rowBuffer->clear();
    display->bufferString(0, "(Green knob):");
    byte lTimeout = Controller::instance->lightsTimeout();
    if(lTimeout > LIGHTS_TIMEOUT_MAX)
        display->bufferString(96, "Never");
    else
        display->bufferString(108, int2str(lTimeout));
    display->drawBufferRow(6);
}
