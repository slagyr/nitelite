#include <Controller.h>
#include "YourBreathMode.h"

#define STEPS 50.0

YourBreathMode::YourBreathMode() : Mode() {
}

const char *YourBreathMode::getName() {
    return "Your Color Breathing";
}

void YourBreathMode::enter() {
    up = true;
    step = STEPS;
    Controller::instance->setScreen(Controller::instance->rgbScreen);
    Controller::instance->readRGB();
    Controller::instance->writeRGBInputs();
}

void YourBreathMode::tick() {
    Controller::instance->readRGB();

    byte rLimit = Controller::instance->redInput;
    byte gLimit = Controller::instance->greenInput;
    byte bLimit = Controller::instance->blueInput;
    float rStep = rLimit < SOFT_LOW_LIMIT ? 0 : (rLimit - SOFT_LOW_LIMIT) / STEPS;
    float gStep = gLimit < SOFT_LOW_LIMIT ? 0 : (gLimit - SOFT_LOW_LIMIT) / STEPS;
    float bStep = bLimit < SOFT_LOW_LIMIT ? 0 : (bLimit - SOFT_LOW_LIMIT) / STEPS;

    if(Controller::instance->red > rLimit)
        Controller::instance->red = rLimit;
    if(Controller::instance->green > gLimit)
        Controller::instance->green = gLimit;
    if(Controller::instance->blue > bLimit)
        Controller::instance->blue = bLimit;

    if(!up) {
        rStep *= -1;
        gStep *= -1;
        bStep *= -1;
        rLimit = minb(SOFT_LOW_LIMIT, rLimit);
        gLimit = minb(SOFT_LOW_LIMIT, gLimit);
        bLimit = minb(SOFT_LOW_LIMIT, bLimit);
    }

    bool done = fade(rStep, gStep, bStep, rLimit, gLimit, bLimit);

    if(done) {
        up = !up;
        Controller::instance->red = rLimit;
        Controller::instance->green = gLimit;
        Controller::instance->blue = bLimit;
    }

    Controller::instance->writeRGB();
}
