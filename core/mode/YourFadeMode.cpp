#include <Controller.h>
#include "YourFadeMode.h"

#define STEPS 50;

YourFadeMode::YourFadeMode(Controller *controller) : Mode(controller) {
}

const char *YourFadeMode::getName() {
    return "Your Fade";
}

void YourFadeMode::enter() {
    up = true;
    step = STEPS;
    controller->setScreen(controller->rgbScreen);
}

void YourFadeMode::tick() {
    controller->readRGB();

    byte rLimit = controller->redInput;
    float rStep = (float)rLimit / STEPS;
    byte gLimit = controller->greenInput;
    float gStep = (float)gLimit / STEPS;
    byte bLimit = controller->blueInput;
    float bStep = (float)bLimit / STEPS;

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
        rLimit = 0;
        gLimit = 0;
        bLimit = 0;
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
