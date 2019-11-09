#include <Controller.h>
#include "YourColorMode.h"

YourColorMode::YourColorMode() : Mode() {}

const char *YourColorMode::getName() {
    return "Your Color";
}

void YourColorMode::enter() {
    Controller::instance->setScreen(Controller::instance->rgbScreen);
}

void YourColorMode::tick() {
    Controller::instance->readRGB();
    Controller::instance->writeRGBInputs();
}
