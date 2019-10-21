#include <Controller.h>
#include "YourBreathMode.h"

#define STEPS 50.0

YourBreathMode::YourBreathMode(Controller *controller) : Mode(controller) {
}

const char *YourBreathMode::getName() {
    return "Your Color Breathing";
}

void YourBreathMode::enter() {
    up = true;
    step = STEPS;
    controller->setScreen(controller->rgbScreen);
    controller->readRGB();
    controller->writeRGBInputs();
}

void YourBreathMode::tick() {
    controller->readRGB();

    byte rLimit = controller->redInput;
    byte gLimit = controller->greenInput;
    byte bLimit = controller->blueInput;
    float rStep = rLimit < SOFT_LOW_LIMIT ? 0 : (rLimit - SOFT_LOW_LIMIT) / STEPS;
    float gStep = gLimit < SOFT_LOW_LIMIT ? 0 : (gLimit - SOFT_LOW_LIMIT) / STEPS;
    float bStep = bLimit < SOFT_LOW_LIMIT ? 0 : (bLimit - SOFT_LOW_LIMIT) / STEPS;

    if(controller->red > rLimit)
        controller->red = rLimit;
    if(controller->green > gLimit)
        controller->green = gLimit;
    if(controller->blue > bLimit)
        controller->blue = bLimit;

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
        controller->red = rLimit;
        controller->green = gLimit;
        controller->blue = bLimit;
    }

    controller->writeRGB();
}
