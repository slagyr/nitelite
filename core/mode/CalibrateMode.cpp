#include <Controller.h>
#include <screen/CalibrateScreen.h>
#include "CalibrateMode.h"

CalibrateMode::CalibrateMode() : Mode() {
    configScreen = new CalibrateScreen();
}

const char *CalibrateMode::getName() {
    return "Calibration";
}

void CalibrateMode::enter() {
    Controller::instance->setScreen(configScreen);

    Config *config = Controller::instance->config;
    config->version = CONFIG_VERSION;
    config->rMin = 1023;
    config->gMin = 1023;
    config->bMin = 1023;
    config->rMax = 0;
    config->gMax = 0;
    config->bMax = 0;
}

void CalibrateMode::tick() {
    Config *config = Controller::instance->config;

    short r = Controller::instance->hardware->readAnalogPin(R_IN_PIN);
    if(r < config->rMin)
        config->rMin = r;
    if(r > config->rMax)
        config->rMax = r;

    short g = Controller::instance->hardware->readAnalogPin(G_IN_PIN);
    if(g < config->gMin)
        config->gMin = g;
    if(g > config->gMax)
        config->gMax = g;

    short b = Controller::instance->hardware->readAnalogPin(B_IN_PIN);
    if(b < config->bMin)
        config->bMin = b;
    if(b > config->bMax)
        config->bMax = b;

    Controller::instance->hardware->saveConfig(config);
}
