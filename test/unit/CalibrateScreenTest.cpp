#include <gtest/gtest.h>
#include "screen/CalibrateScreen.h"
#include "MockController.h"
#include "testutil.h"

class ConfigScreenTest : public ::testing::Test {
protected:

    MockController *controller;
    Screen *screen;

    virtual void SetUp() {
        controller = MockController::create();
        screen = new CalibrateScreen();
    }

    virtual void TearDown() {
        delete screen;
        delete controller;
    }
};

TEST_F(ConfigScreenTest, Hardcoding) {
    EXPECT_EQ("Calibration", screen->getName());
}

//TEST_F(ConfigScreenTest, Preview) {
//    controller->minR = 1;
//    controller->maxR = 1023;
//    controller->minG = 99;
//    controller->maxG = 999;
//    controller->minB = 1000;
//    controller->maxB = 314;
//    screen->enter();
//
//    print_buffer(controller->display->getBuffer());
//}


