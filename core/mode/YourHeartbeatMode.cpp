#include <Controller.h>
#include "YourHeartbeatMode.h"

#define NOMINAL_STEPS 120.0;
#define DOWN_GAIN 0.85
#define UP_GAIN 3.0
#define MIN_MULTIPLIER 0.5

YourHeartbeatMode::YourHeartbeatMode() : Mode() {
}

const char *YourHeartbeatMode::getName() {
    return "Your Color Heartbeat";
}

void YourHeartbeatMode::enter() {
    up = false;
    multiplier = 20;
    Controller::instance->setScreen(Controller::instance->rgbScreen);
    Controller::instance->readRGB();
    Controller::instance->writeRGBInputs();
}

void YourHeartbeatMode::tick() {
    Controller::instance->readRGB();

    byte rLimit = Controller::instance->redInput;
    byte gLimit = Controller::instance->greenInput;
    byte bLimit = Controller::instance->blueInput;
    float rStep = rLimit < SOFT_LOW_LIMIT ? 0 : (rLimit - SOFT_LOW_LIMIT) / NOMINAL_STEPS;
    float gStep = gLimit < SOFT_LOW_LIMIT ? 0 : (gLimit - SOFT_LOW_LIMIT) / NOMINAL_STEPS;
    float bStep = bLimit < SOFT_LOW_LIMIT ? 0 : (bLimit - SOFT_LOW_LIMIT) / NOMINAL_STEPS;
    rStep *= multiplier;
    gStep *= multiplier;
    bStep *= multiplier;

    multiplier *= up ? UP_GAIN : DOWN_GAIN;
    if(multiplier < MIN_MULTIPLIER)
        multiplier = MIN_MULTIPLIER;


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
        multiplier = up ? MIN_MULTIPLIER : 20;
        Controller::instance->red = rLimit;
        Controller::instance->green = gLimit;
        Controller::instance->blue = bLimit;
    }

    Controller::instance->writeRGB();
}
