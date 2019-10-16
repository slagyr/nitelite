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
    EXPECT_STREQ("RGB", controller->rgbScreen->getName());
    EXPECT_EQ(controller->splashScreen, controller->getScreen());
}

TEST_F(ControllerTest, Modes) {
    EXPECT_EQ("Your Color", controller->modes->get(0)->getName());
    EXPECT_EQ("Your Color", controller->getMode()->getName());
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

    EXPECT_STREQ("RGB", controller->getScreen()->getName());
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

TEST_F(ControllerTest, ReadRGB) {
    hardware->analogReads[R_IN_PIN].push(001);
    hardware->analogReads[G_IN_PIN].push(512);
    hardware->analogReads[B_IN_PIN].push(1023);

    controller->readRGB();

    EXPECT_EQ(0, controller->redInput);
    EXPECT_EQ(127, controller->greenInput);
    EXPECT_EQ(255, controller->blueInput);
}

TEST_F(ControllerTest, WriteRGB) {
    controller->writeRGB(100, 200, 123);

    EXPECT_EQ(100, controller->red);
    ASSERT_EQ(false, hardware->analogWrites[R_OUT_PIN].empty());
    EXPECT_EQ(100, hardware->analogWrites[R_OUT_PIN].front());

    EXPECT_EQ(200, controller->green);
    ASSERT_EQ(false, hardware->analogWrites[G_OUT_PIN].empty());
    EXPECT_EQ(200, hardware->analogWrites[G_OUT_PIN].front());

    EXPECT_EQ(123, controller->blue);
    ASSERT_EQ(false, hardware->analogWrites[B_OUT_PIN].empty());
    EXPECT_EQ(123, hardware->analogWrites[B_OUT_PIN].front());
}

