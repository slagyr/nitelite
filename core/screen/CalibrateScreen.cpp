#include <oled/OledFonts.h>
#include "CalibrateScreen.h"
#include "Controller.h"
#include "core.h"
#include "string.h"

CalibrateScreen::CalibrateScreen() : Screen() {}

const char *CalibrateScreen::getName() {
    return "Calibration";
}

void CalibrateScreen::enter() {
    Oled *display = Controller::instance->display;
    display->clearScreen();

    display->rowBuffer->clear();
    display->rowBuffer->drawLine(0, 1, 128, 1, WHITE);
    display->drawCanvas(0, 1, 128, 8, display->rowBuffer->getBuffer());

    display->setFont(oled_font6x8);
    display->writeString(1, 0, "Calibration");

    update();
}

void CalibrateScreen::update() {
    Oled *display = Controller::instance->display;
    Canvas *rowBuffer = display->rowBuffer;

    display->setFont(oled_font8x8);

    rowBuffer->clear();
    display->bufferString(16, "RED:");
    display->bufferString(56, int2str(Controller::instance->config->rMin));
    display->bufferString(96, int2str(Controller::instance->config->rMax));
    display->drawBufferRow(2);

    rowBuffer->clear();
    display->bufferString(0, "GREEN:");
    display->bufferString(56, int2str(Controller::instance->config->gMin));
    display->bufferString(96, int2str(Controller::instance->config->gMax));
    display->drawBufferRow(4);

    rowBuffer->clear();
    display->bufferString(8, "BLUE:");
    display->bufferString(56, int2str(Controller::instance->config->bMin));
    display->bufferString(96, int2str(Controller::instance->config->bMax));
    display->drawBufferRow(6);
}
