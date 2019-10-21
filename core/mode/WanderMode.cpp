#include <Controller.h>
#include "WanderMode.h"

#define WANDER_STEPS 25.0

WanderMode::WanderMode(Controller *controller) : Mode(controller) {
    dest = new Color();
}

const char *WanderMode::getName() {
    return "Wandering Color";
}

void WanderMode::enter() {
    controller->setScreen(controller->rgbScreen);
    randomColor(dest);
    controller->red = dest->r;
    controller->green = dest->g;
    controller->blue = dest->b;
    chooseDest();
}

void WanderMode::tick() {
    bool done = fade(rStep, gStep, bStep, dest->r, dest->g, dest->b);
    if(done)
        chooseDest();

    controller->writeRGB();
}

void WanderMode::chooseDest() {
    randomColor(dest);
    rStep = ((short) dest->r - controller->red) / WANDER_STEPS;
    gStep = ((short) dest->g - controller->green) / WANDER_STEPS;
    bStep = ((short) dest->b - controller->blue) / WANDER_STEPS;
}
