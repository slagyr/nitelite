#include "ChristmasMode.h"

ChristmasMode::ChristmasMode(Controller *controller) : TravelingMode(controller) {
    state = 3;
}

const char *ChristmasMode::getName() {
    return "Christmas";
}

void ChristmasMode::nextColor() {
    state++;
    if(state > 3)
        state = 0;
    if(state == 0) {
        dest->r = 255;
        dest->g = 0;
        dest->b = 0;
    } else if(state == 1) {
        dest->r = 255;
        dest->g = 255;
        dest->b = 255;
    } else if(state == 2) {
        dest->r = 0;
        dest->g = 255;
        dest->b = 0;
    } else {
        dest->r = 255;
        dest->g = 255;
        dest->b = 255;
    }
}
