#include <Controller.h>
#include <screen/SettingsScreen.h>
#include "SettingsMode.h"

SettingsMode::SettingsMode(Controller *controller) : Mode(controller) {}

const char *SettingsMode::getName() {
    return "Settings";
}

void SettingsMode::enter() {
    Screen *configScreen = new SettingsScreen(controller);
    controller->setScreen(configScreen);
}

void SettingsMode::tick() {
    Config *config = controller->config;

    controller->readRGB();

    config->screenTimeout = controller->redInput;
    config->lightsTimeout = controller->greenInput;

    controller->hardware->saveConfig(config);
}
