#include <Controller.h>
#include <screen/ConfigScreen.h>
#include "ConfigMode.h"

ConfigMode::ConfigMode(Controller *controller) : Mode(controller) {}

const char *ConfigMode::getName() {
    return "Config";
}

void ConfigMode::enter() {
    Screen *configScreen = new ConfigScreen(controller);
    controller->setScreen(configScreen);

    Config *config = controller->config;
    config->version = CONFIG_VERSION;
    config->rMin = 1023;
    config->gMin = 1023;
    config->bMin = 1023;
    config->rMax = 0;
    config->gMax = 0;
    config->bMax = 0;
}

void ConfigMode::tick() {
    Config *config = controller->config;

    short r = controller->hardware->readAnalogPin(R_IN_PIN);
    if(r < config->rMin)
        config->rMin = r;
    if(r > config->rMax)
        config->rMax = r;

    short g = controller->hardware->readAnalogPin(G_IN_PIN);
    if(g < config->gMin)
        config->gMin = g;
    if(g > config->gMax)
        config->gMax = g;

    short b = controller->hardware->readAnalogPin(B_IN_PIN);
    if(b < config->bMin)
        config->bMin = b;
    if(b > config->bMax)
        config->bMax = b;

    controller->hardware->saveConfig(config);
}
