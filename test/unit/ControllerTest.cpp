#include <gtest/gtest.h>
#include "Controller.h"
#include "MockHardware.h"
#include "MockDisplay.h"
#include "MockScreen.h"

class ControllerTest : public ::testing::Test {
protected:

    Controller *controller;
    MockHardware *hardware;
    MockDisplay *display;
    MockScreen *screen;

    virtual void SetUp() {
        controller = new Controller();

        controller->hardware = hardware = new MockHardware();
        controller->display = display = new MockDisplay();

        screen = new MockScreen(controller);
        controller->setup();
    }

    virtual void TearDown() {
        delete hardware;
        delete controller;
        delete display;
        delete screen;
    }
};

TEST_F(ControllerTest, Screens) {
    EXPECT_STREQ("Splash", controller->splashScreen->getName());
    EXPECT_STREQ("Home", controller->homeScreen->getName());
    EXPECT_EQ(controller->splashScreen, controller->getScreen());
}

TEST_F(ControllerTest, Setup) {
    controller->setup();

    EXPECT_EQ("INPUT", hardware->pinModes[R_IN_PIN]);
    EXPECT_EQ("INPUT", hardware->pinModes[G_IN_PIN]);
    EXPECT_EQ("INPUT", hardware->pinModes[B_IN_PIN]);
    EXPECT_EQ("OUTPUT", hardware->pinModes[R_OUT_PIN]);
    EXPECT_EQ("OUTPUT", hardware->pinModes[G_OUT_PIN]);
    EXPECT_EQ("OUTPUT", hardware->pinModes[B_OUT_PIN]);
    EXPECT_EQ("OUTPUT", hardware->pinModes[OLED_PIN]);
    EXPECT_EQ(false, display->wasSetup);
}

TEST_F(ControllerTest, ScreenTimeout) {
    screen->timeout = 123;
    controller->setScreen(screen);

    controller->tick(1111);

    EXPECT_STREQ("Home", controller->getScreen()->getName());
}

TEST_F(ControllerTest, EnteringScreen) {
    EXPECT_EQ(false, screen->entered);

    controller->setScreen(screen);

    EXPECT_EQ(true, screen->entered);
}

TEST_F(ControllerTest, DisplayOn) {
    controller->displayOn();

    EXPECT_EQ("HIGH", hardware->digitalWrites[OLED_PIN]);
    EXPECT_EQ(true, display->wasSetup);
}

TEST_F(ControllerTest, DisplayOff) {
    controller->displayOn();
    controller->displayOff();

    EXPECT_EQ("LOW", hardware->digitalWrites[OLED_PIN]);
}