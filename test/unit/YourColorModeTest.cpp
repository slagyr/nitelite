#include <gtest/gtest.h>
#include "mode/YourColorMode.h"
#include "MockController.h"

class YourColorModeTest : public ::testing::Test {
protected:

    MockController *controller;
    Mode *mode;

    virtual void SetUp() {
        controller = MockController::create();
        mode = new YourColorMode();
        controller->setScreen(controller->splashScreen);
    }

    virtual void TearDown() {
        delete mode;
        delete controller;
    }
};

TEST_F(YourColorModeTest, Name) {
    EXPECT_EQ("Your Color", mode->getName());
}

TEST_F(YourColorModeTest, Enter) {
    mode->enter();

    EXPECT_EQ("RGB", controller->screen->getName());
}

