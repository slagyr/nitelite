#include <Controller.h>
#include "SleepMode.h"

SleepMode::SleepMode() : Mode() {}

const char *SleepMode::getName() {
    return "Sleep";
}

void SleepMode::enter() {
    Controller::instance->setScreen(Controller::instance->rgbScreen);
}

void SleepMode::tick() {
    Controller::instance->writeRGB(0, 0, 0);
}
