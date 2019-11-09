#include <Controller.h>
#include "TravelingMode.h"

#define TRAVEL_STEPS 20

TravelingMode::TravelingMode() : Mode() {
    dest = new Color();
}

const char *TravelingMode::getName() {
    return "Traveling Color";
}

void TravelingMode::enter() {
    Controller::instance->setScreen(Controller::instance->rgbScreen);
    nextColor();
    Controller::instance->red = dest->r;
    Controller::instance->green = dest->g;
    Controller::instance->blue = dest->b;
    chooseDest();
    traveling = true;
}

void TravelingMode::nextColor() { randomColor(dest); }

void TravelingMode::tick() {
    if (traveling) {
        bool done = fade(rStep, gStep, bStep, dest->r, dest->g, dest->b);
        if (done)
            traveling = false;
    } else {
        if(step >= TRAVEL_STEPS) {
            traveling = true;
            step = 0;
            chooseDest();
        }
        else
            step++;
    }

    Controller::instance->writeRGB();
}

void TravelingMode::chooseDest() {
    nextColor();
    rStep = ((short) dest->r - Controller::instance->red) / TRAVEL_STEPS;
    gStep = ((short) dest->g - Controller::instance->green) / TRAVEL_STEPS;
    bStep = ((short) dest->b - Controller::instance->blue) / TRAVEL_STEPS;
}
