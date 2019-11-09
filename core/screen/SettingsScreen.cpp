#include <oled/OledFonts.h>
#include "SettingsScreen.h"
#include "Controller.h"
#include "common.h"
#include "string.h"

SettingsScreen::SettingsScreen(Controller *controller) : Screen(controller) {}

const char *SettingsScreen::getName() {
    return "Settings";
}

void SettingsScreen::enter() {
    Oled *display = controller->display;
    display->clearScreen();

    display->rowBuffer->clear();
    display->rowBuffer->drawLine(0, 1, 128, 1, WHITE);
    display->drawCanvas(0, 1, 128, 8, display->rowBuffer->getBuffer());

    display->setFont(oled_font6x8);
    display->writeString(1, 0, "Settings");

    update();
}

void SettingsScreen::update() {
    Oled *display = controller->display;
    Canvas *rowBuffer = display->rowBuffer;

    display->setFont(oled_font6x8);

    rowBuffer->clear();
    display->bufferString(0, "Screen Timeout Secs");
    display->drawBufferRow(2);

    rowBuffer->clear();
    display->bufferString(0, "(Red knob):");
    byte sTimeout = controller->screenTimeout();
    if(sTimeout > SCREEN_TIMEOUT_MAX)
        display->bufferString(84, "Never");
    else
        display->bufferString(84, int2str(sTimeout));
    display->drawBufferRow(3);

    rowBuffer->clear();
    display->bufferString(0, "Lights Timeout Mins:");
    display->drawBufferRow(5);

    rowBuffer->clear();
    display->bufferString(0, "(Green knob):");
    byte lTimeout = controller->lightsTimeout();
    if(sTimeout > LIGHTS_TIMEOUT_MAX)
        display->bufferString(84, "Never");
    else
        display->bufferString(84, int2str(lTimeout));
    display->drawBufferRow(6);
}
