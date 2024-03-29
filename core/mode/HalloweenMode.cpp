#include <Controller.h>
#include "HalloweenMode.h"

#define HALLOWEEN_LIGHTNING_FADE -0.2

HalloweenMode::HalloweenMode() : TravelingMode() {
    state = 2;
    lightning = false;
}

const char *HalloweenMode::getName() {
    return "Halloween";
}

void HalloweenMode::nextColor() {
    state++;
    if(state > 2)
        state = 0;
    if(state == 0) { // Purple
        dest->r = 128;
        dest->g = 0;
        dest->b = 128;
    } else if(state == 1) { // Orange
        dest->r = 180;
        dest->g = 60;
        dest->b = 0;
    } else { // Green
        dest->r = 0;
        dest->g = 180;
        dest->b = 0;
    }
}

void HalloweenMode::tick() {
    if(Controller::instance->hardware->randomLong(50) == 0) {
        lightning = true;
        Controller::instance->writeRGB(255, 255, 255);
    } else if(lightning) {
        float rStep = minf(-1.0, (Controller::instance->red - dest->r) * HALLOWEEN_LIGHTNING_FADE);
        float gStep = minf(-1.0, (Controller::instance->green - dest->g) * HALLOWEEN_LIGHTNING_FADE);
        float bStep = minf(-1.0, (Controller::instance->blue - dest->b) * HALLOWEEN_LIGHTNING_FADE);

        bool done = fade(rStep, gStep, bStep, dest->r, dest->g, dest->b);
        Controller::instance->writeRGB();
        if(done)
            lightning = false;
    } else
        TravelingMode::tick();
}
