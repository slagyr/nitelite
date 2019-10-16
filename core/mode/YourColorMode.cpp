#include <Controller.h>
#include "YourColorMode.h"

YourColorMode::YourColorMode(Controller *controller) : Mode(controller) {}

const char *YourColorMode::getName() {
    return "Your Color";
}

void YourColorMode::enter() {
    controller->setScreen(controller->rgbScreen);
}

void YourColorMode::tick() {
    controller->readRGB();
    controller->writeRGBInputs();
}
