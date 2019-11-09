#include <Controller.h>
#include "WanderMode.h"

#define WANDER_STEPS 25.0

WanderMode::WanderMode() : Mode() {
    dest = new Color();
}

const char *WanderMode::getName() {
    return "Wandering Color";
}

void WanderMode::enter() {
    Controller::instance->setScreen(Controller::instance->rgbScreen);
    randomColor(dest);
    Controller::instance->red = dest->r;
    Controller::instance->green = dest->g;
    Controller::instance->blue = dest->b;
    chooseDest();
}

void WanderMode::tick() {
    bool done = fade(rStep, gStep, bStep, dest->r, dest->g, dest->b);
    if(done)
        chooseDest();

    Controller::instance->writeRGB();
}

void WanderMode::chooseDest() {
    randomColor(dest);
    rStep = ((short) dest->r - Controller::instance->red) / WANDER_STEPS;
    gStep = ((short) dest->g - Controller::instance->green) / WANDER_STEPS;
    bStep = ((short) dest->b - Controller::instance->blue) / WANDER_STEPS;
}
