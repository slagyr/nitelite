#include "RWBMode.h"

RWBMode::RWBMode() : TravelingMode() {
    state = 2;
}

const char *RWBMode::getName() {
    return "Star Spangled Banner";
}

void RWBMode::nextColor() {
    state++;
    if(state > 2)
        state = 0;
    if(state == 0) {
        dest->r = 255;
        dest->g = 0;
        dest->b = 0;
    } else if(state == 1) {
        dest->r = 255;
        dest->g = 255;
        dest->b = 255;
    } else {
        dest->r = 0;
        dest->g = 0;
        dest->b = 255;
    }
}
