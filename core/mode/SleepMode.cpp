#include <Controller.h>
#include "SleepMode.h"

SleepMode::SleepMode(Controller *controller) : Mode(controller) {}

const char *SleepMode::getName() {
    return "Sleep";
}

void SleepMode::enter() {
    controller->setScreen(controller->rgbScreen);
}

void SleepMode::tick() {
    controller->writeRGB(0, 0, 0);
}
