#include <Controller.h>
#include <screen/SettingsScreen.h>
#include "SettingsMode.h"

SettingsMode::SettingsMode() : Mode() {
    settingsScreen = new SettingsScreen();
}

const char *SettingsMode::getName() {
    return "Settings";
}

void SettingsMode::enter() {
    Controller::instance->setScreen(settingsScreen);
}

void SettingsMode::tick() {
    Config *config = Controller::instance->config;

    Controller::instance->readRGB();

    config->screenTimeout = Controller::instance->redInput;
    config->lightsTimeout = Controller::instance->greenInput;

    Controller::instance->hardware->saveConfig(config);
}
