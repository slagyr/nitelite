#include <gtest/gtest.h>
#include "mode/SettingsMode.h"
#include "MockController.h"

class SettingsModeTest : public ::testing::Test {
protected:

    MockController *controller;
    MockHardware *hardware;
    Mode *mode;

    virtual void SetUp() {
        controller = MockController::create();
        hardware = (MockHardware*)controller->hardware;
        mode = new SettingsMode(controller);
    }

    virtual void TearDown() {
        delete mode;
        delete controller;
    }
};

TEST_F(SettingsModeTest, Name) {
    EXPECT_EQ("Settings", mode->getName());
}

TEST_F(SettingsModeTest, Enter) {
    mode->enter();

    EXPECT_EQ("Settings", controller->getScreen()->getName());
}

TEST_F(SettingsModeTest, SavesMinMaxToSettings) {
    Config *config = controller->config;
    config->rMin = 0;
    config->rMax = 255;
    config->gMin = 0;
    config->gMax = 255;

    mode->enter();

    hardware->analogReads[R_IN_PIN].push(0);
    hardware->analogReads[G_IN_PIN].push(0);

    mode->tick();

    EXPECT_EQ(255, hardware->config->screenTimeout);
    EXPECT_EQ(255, hardware->config->lightsTimeout);

    hardware->analogReads[R_IN_PIN].push(100);
    hardware->analogReads[G_IN_PIN].push(200);

    mode->tick();

    EXPECT_EQ(155, hardware->config->screenTimeout);
    EXPECT_EQ(55, hardware->config->lightsTimeout);
}

