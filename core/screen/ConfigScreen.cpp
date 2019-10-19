#include <oled/OledFonts.h>
#include "ConfigScreen.h"
#include "Controller.h"
#include "common.h"
#include "string.h"

ConfigScreen::ConfigScreen(Controller *controller) : Screen(controller) {}

const char *ConfigScreen::getName() {
    return "Config";
}

void ConfigScreen::enter() {
    Oled *display = controller->display;
    display->clearScreen();

    display->rowBuffer->clear();
    display->rowBuffer->drawLine(0, 1, 128, 1, WHITE);
    display->drawCanvas(0, 1, 128, 8, display->rowBuffer->getBuffer());

    display->setFont(oled_font6x8);
    display->writeString(1, 0, "Config");

    update();
}

void ConfigScreen::update() {
    Oled *display = controller->display;
    Canvas *rowBuffer = display->rowBuffer;

    display->setFont(oled_font8x8);

    rowBuffer->clear();
    display->bufferString(16, "RED:");
    display->bufferString(56, int2str(controller->config->rMin));
    display->bufferString(96, int2str(controller->config->rMax));
    display->drawBufferRow(2);

    rowBuffer->clear();
    display->bufferString(0, "GREEN:");
    display->bufferString(56, int2str(controller->config->gMin));
    display->bufferString(96, int2str(controller->config->gMax));
    display->drawBufferRow(4);

    rowBuffer->clear();
    display->bufferString(8, "BLUE:");
    display->bufferString(56, int2str(controller->config->bMin));
    display->bufferString(96, int2str(controller->config->bMax));
    display->drawBufferRow(6);
}
