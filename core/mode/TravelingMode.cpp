#include <Controller.h>
#include "TravelingMode.h"

#define TRAVEL_STEPS 20

TravelingMode::TravelingMode(Controller *controller) : Mode(controller) {
    dest = new Color();
}

const char *TravelingMode::getName() {
    return "Traveling Color";
}

void TravelingMode::enter() {
    controller->setScreen(controller->rgbScreen);
    nextColor();
    controller->red = dest->r;
    controller->green = dest->g;
    controller->blue = dest->b;
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

    controller->writeRGB();
}

void TravelingMode::chooseDest() {
    nextColor();
    rStep = ((short) dest->r - controller->red) / TRAVEL_STEPS;
    gStep = ((short) dest->g - controller->green) / TRAVEL_STEPS;
    bStep = ((short) dest->b - controller->blue) / TRAVEL_STEPS;
}
