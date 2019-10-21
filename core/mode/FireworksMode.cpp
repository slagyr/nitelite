#include <Controller.h>
#include "FireworksMode.h"

#define FIREWORKS_STEP_PERCENT -0.1

FireworksMode::FireworksMode(Controller *controller) : Mode(controller) {
    color = new Color();
}

const char *FireworksMode::getName() {
    return "Fireworks";

}

void FireworksMode::enter() {
    controller->setScreen(controller->rgbScreen);
    chooseColor();
    controller->writeRGB(color->r, color->g, color->b);
}

void FireworksMode::chooseColor() { randomBrightColor(color); }

void FireworksMode::tick() {
    if(controller->hardware->randomLong(20) == 0) {
        chooseColor();
        if(color->r != 0)
            controller->red = color->r;
        if(color->g != 0)
            controller->green = color->g;
        if(color->b != 0)
            controller->blue = color->b;
    }

    float rStep = controller->red * FIREWORKS_STEP_PERCENT;
    float gStep = controller->green * FIREWORKS_STEP_PERCENT;
    float bStep = controller->blue * FIREWORKS_STEP_PERCENT;

    fade(rStep, gStep, bStep, 0, 0, 0);

    controller->writeRGB();
}
