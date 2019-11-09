#include <Controller.h>
#include "FireworksMode.h"

#define FIREWORKS_STEP_PERCENT -0.1

FireworksMode::FireworksMode() : Mode() {
    color = new Color();
}

const char *FireworksMode::getName() {
    return "Fireworks";

}

void FireworksMode::enter() {
    Controller::instance->setScreen(Controller::instance->rgbScreen);
    chooseColor();
    Controller::instance->writeRGB(color->r, color->g, color->b);
}

void FireworksMode::chooseColor() { randomBrightColor(color); }

void FireworksMode::tick() {
    if(Controller::instance->hardware->randomLong(20) == 0) {
        chooseColor();
        if(color->r != 0)
            Controller::instance->red = color->r;
        if(color->g != 0)
            Controller::instance->green = color->g;
        if(color->b != 0)
            Controller::instance->blue = color->b;
    }

    float rStep = Controller::instance->red * FIREWORKS_STEP_PERCENT;
    float gStep = Controller::instance->green * FIREWORKS_STEP_PERCENT;
    float bStep = Controller::instance->blue * FIREWORKS_STEP_PERCENT;

    fade(rStep, gStep, bStep, 0, 0, 0);

    Controller::instance->writeRGB();
}
