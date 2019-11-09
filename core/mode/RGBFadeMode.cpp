#include <Controller.h>
#include "RGBFadeMode.h"

#define R2G 0
#define G2B 1
#define B2R 2
#define RGB_FADE_STEP 5

RGBFadeMode::RGBFadeMode() : Mode() {
}

const char *RGBFadeMode::getName() {
    return "RGB Fade";
}

void RGBFadeMode::enter() {
    state = R2G;
    Controller::instance->setScreen(Controller::instance->rgbScreen);
    Controller::instance->red = 255;
    Controller::instance->green = 0;
    Controller::instance->blue = 0;
}

void RGBFadeMode::tick() {
    Controller::instance->readRGB();
    switch (state) {
        case R2G:
            if (fade(-RGB_FADE_STEP, RGB_FADE_STEP, 0, 0, 255, 1))
                state = G2B;
            break;
        case G2B:
            if (fade(0, -RGB_FADE_STEP, RGB_FADE_STEP, 1, 0, 255))
                state = B2R;
            break;
        case B2R:
            if (fade(RGB_FADE_STEP, 0, -RGB_FADE_STEP, 255, 1, 0))
                state = R2G;
            break;
    }

    Controller::instance->writeRGB();
}
