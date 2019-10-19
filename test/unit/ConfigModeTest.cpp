#include <gtest/gtest.h>
#include "mode/ConfigMode.h"
#include "MockController.h"

class ConfigModeTest : public ::testing::Test {
protected:

    MockController *controller;
    MockHardware *hardware;
    Mode *mode;

    virtual void SetUp() {
        controller = MockController::create();
        hardware = (MockHardware*)controller->hardware;
        mode = new ConfigMode(controller);
    }

    virtual void TearDown() {
        delete mode;
        delete controller;
    }
};

TEST_F(ConfigModeTest, Name) {
    EXPECT_EQ("Config", mode->getName());
}

TEST_F(ConfigModeTest, Enter) {
    mode->enter();

    EXPECT_EQ("Config", controller->getScreen()->getName());
}

TEST_F(ConfigModeTest, SavesMinMaxToConfig) {
    mode->enter();

    hardware->analogReads[R_IN_PIN].push(999);
    hardware->analogReads[G_IN_PIN].push(998);
    hardware->analogReads[B_IN_PIN].push(997);

    mode->tick();

    EXPECT_EQ(999, hardware->config->rMax);
    EXPECT_EQ(998, hardware->config->gMax);
    EXPECT_EQ(997, hardware->config->bMax);

    hardware->analogReads[R_IN_PIN].push(12);
    hardware->analogReads[G_IN_PIN].push(13);
    hardware->analogReads[B_IN_PIN].push(14);

    mode->tick();

    EXPECT_EQ(12, hardware->config->rMin);
    EXPECT_EQ(13, hardware->config->gMin);
    EXPECT_EQ(14, hardware->config->bMin);
}
