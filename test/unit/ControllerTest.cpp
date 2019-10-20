#include <gtest/gtest.h>
#include "Controller.h"
#include "oled/Oled.h"
#include "MockOledComm.h"
#include "MockHardware.h"
#include "MockScreen.h"

class ControllerTest : public ::testing::Test {
protected:

    Controller *controller;
    MockHardware *hardware;
    MockOledComm *oledComm;
    Oled *display;
    MockScreen *screen;

    virtual void SetUp() {
        hardware = new MockHardware();
        controller = new Controller(hardware);

        oledComm = new MockOledComm();
        controller->display = display = new Oled(hardware, oledComm);

        screen = new MockScreen(controller);
        controller->setup();
    }

    virtual void TearDown() {
        delete hardware;
        delete controller;
        delete display;
        delete oledComm;
        delete screen;
    }
};

TEST_F(ControllerTest, Screens) {
    EXPECT_STREQ("Splash", controller->splashScreen->getName());
    EXPECT_STREQ("RGB", controller->rgbScreen->getName());
    EXPECT_EQ(controller->rgbScreen, controller->getScreen());
}

TEST_F(ControllerTest, Buttons) {
    EXPECT_EQ(UP_PIN, controller->upButton->pin());
    EXPECT_EQ(DOWN_PIN, controller->downButton->pin());
}

TEST_F(ControllerTest, Modes) {
    EXPECT_EQ("Your Color", controller->modes[0]->getName());
    EXPECT_EQ("Your Color Breathing", controller->modes[1]->getName());
    EXPECT_EQ("Your Color Heartbeat", controller->modes[2]->getName());
    EXPECT_EQ("RGB Fade", controller->modes[3]->getName());

    EXPECT_EQ("Your Color", controller->getMode()->getName());
    EXPECT_EQ(0, controller->modeIndex);
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
    EXPECT_EQ(false, oledComm->wasSetup);
}

TEST_F(ControllerTest, SetupDefaultConfig) {
    controller->setup();

    EXPECT_EQ(1, controller->config->version);
    EXPECT_EQ(0, controller->config->rMin);
    EXPECT_EQ(0, controller->config->gMin);
    EXPECT_EQ(0, controller->config->bMin);
    EXPECT_EQ(1023, controller->config->rMax);
    EXPECT_EQ(1023, controller->config->gMax);
    EXPECT_EQ(1023, controller->config->bMax);
}

TEST_F(ControllerTest, SetupSavedConfig) {
    Config conf;
    conf.version = CONFIG_VERSION;
    conf.rMin = 1;
    conf.gMin = 2;
    conf.bMin = 3;
    conf.rMax = 997;
    conf.gMax = 998;
    conf.bMax = 999;
    hardware->saveConfig(&conf);

    controller->setup();

    EXPECT_EQ(1, controller->config->version);
    EXPECT_EQ(1, controller->config->rMin);
    EXPECT_EQ(2, controller->config->gMin);
    EXPECT_EQ(3, controller->config->bMin);
    EXPECT_EQ(997, controller->config->rMax);
    EXPECT_EQ(998, controller->config->gMax);
    EXPECT_EQ(999, controller->config->bMax);
}

TEST_F(ControllerTest, TempScreenTimeout) {
    controller->setTempScreen(screen, 123);

    EXPECT_STREQ("Mock Screen", controller->getActiveScreen()->getName());
    EXPECT_EQ(true, screen->wasEntered);

    controller->tick(1111);

    EXPECT_STREQ("RGB", controller->getActiveScreen()->getName());
}

TEST_F(ControllerTest, ScreenUpdate) {
    MockScreen *tempScreen = new MockScreen(controller, "Temp");
    MockScreen *normScreen = new MockScreen(controller, "Notm");

    controller->setScreen(normScreen);
    controller->tick(111);
    EXPECT_EQ(true, normScreen->wasUpdated);
    EXPECT_EQ(false, tempScreen->wasUpdated);
    normScreen->wasUpdated = false;

    controller->setTempScreen(tempScreen, 123);
    controller->tick(222);
    EXPECT_EQ(false, normScreen->wasUpdated);
    EXPECT_EQ(true, tempScreen->wasUpdated);
    tempScreen->wasUpdated = false;

    controller->tick(9999);
    EXPECT_EQ(true, normScreen->wasUpdated);
    EXPECT_EQ(false, tempScreen->wasUpdated);
}

TEST_F(ControllerTest, EnteringScreen) {
    EXPECT_EQ(false, screen->wasEntered);

    controller->setScreen(screen);

    EXPECT_EQ(true, screen->wasEntered);
}

TEST_F(ControllerTest, DisplayOn) {
    controller->displayOn();

    EXPECT_EQ("HIGH", hardware->digitalWrites[OLED_PIN]);
    EXPECT_EQ(true, oledComm->wasSetup);
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

TEST_F(ControllerTest, ReadRGBAlteredConfig) {
    controller->config->rMin = 200;
    controller->config->rMax = 400;
    controller->config->gMin = 100;
    controller->config->gMax = 800;
    controller->config->bMin = 0;
    controller->config->bMax = 1023;
    hardware->analogReads[R_IN_PIN].push(300);
    hardware->analogReads[G_IN_PIN].push(300);
    hardware->analogReads[B_IN_PIN].push(300);

    controller->readRGB();

    EXPECT_EQ(127, controller->redInput);
    EXPECT_EQ(72, controller->greenInput);
    EXPECT_EQ(74, controller->blueInput);
}

TEST_F(ControllerTest, ReadRGBDoesntExceedLimits) {
    controller->config->rMin = 200;
    controller->config->rMax = 400;
    controller->config->gMin = 100;
    controller->config->gMax = 800;
    controller->config->bMin = 0;
    controller->config->bMax = 1023;
    hardware->analogReads[R_IN_PIN].push(1023);
    hardware->analogReads[G_IN_PIN].push(0);
    hardware->analogReads[B_IN_PIN].push(1024);

    controller->readRGB();

    EXPECT_EQ(255, controller->redInput);
    EXPECT_EQ(0, controller->greenInput);
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

TEST_F(ControllerTest, DownPressed) {
    controller->downButton->force(true);

    controller->tick(1);

    EXPECT_EQ(1, controller->modeIndex);
    EXPECT_EQ("Your Color Breathing", controller->getMode()->getName());

    for (int i = 1; i < MODES; i++) {
        controller->downButton->force(true);
        controller->tick(i);
    }

    EXPECT_EQ(0, controller->modeIndex);
    EXPECT_EQ("Your Color", controller->getMode()->getName());
}

TEST_F(ControllerTest, UpPressed) {

    for (int i = 0; i < MODES - 1; i++) {
        controller->upButton->force(true);
        controller->tick(i);
    }

    EXPECT_EQ(1, controller->modeIndex);
    EXPECT_EQ("Your Color Breathing", controller->getMode()->getName());
}
