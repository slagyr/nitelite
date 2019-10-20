#include <Controller.h>
#include "YourBeatMode.h"

#define NOMINAL_STEPS 120.0;
#define DOWN_GAIN 0.85
#define UP_GAIN 3.0
#define MIN_MULTIPLIER 0.5

YourBeatMode::YourBeatMode(Controller *controller) : Mode(controller) {
}

const char *YourBeatMode::getName() {
    return "Your Color Heartbeat";
}

void YourBeatMode::enter() {
    up = false;
    multiplier = 20;
    controller->setScreen(controller->rgbScreen);
    controller->readRGB();
    controller->writeRGBInputs();
}

void YourBeatMode::tick() {
    controller->readRGB();

    byte rLimit = controller->redInput;
    byte gLimit = controller->greenInput;
    byte bLimit = controller->blueInput;
    float rStep = rLimit < SOFT_LOW_LIMIT ? 0 : (rLimit - SOFT_LOW_LIMIT) / NOMINAL_STEPS;
    float gStep = gLimit < SOFT_LOW_LIMIT ? 0 : (gLimit - SOFT_LOW_LIMIT) / NOMINAL_STEPS;
    float bStep = bLimit < SOFT_LOW_LIMIT ? 0 : (bLimit - SOFT_LOW_LIMIT) / NOMINAL_STEPS;
    rStep *= multiplier;
    gStep *= multiplier;
    bStep *= multiplier;

    multiplier *= up ? UP_GAIN : DOWN_GAIN;
    if(multiplier < MIN_MULTIPLIER)
        multiplier = MIN_MULTIPLIER;


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
        multiplier = up ? MIN_MULTIPLIER : 20;
        controller->red = rLimit;
        controller->green = gLimit;
        controller->blue = bLimit;
    }

    controller->writeRGB();
}
