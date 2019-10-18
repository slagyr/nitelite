#include <gtest/gtest.h>
#include "screen/RGBScreen.h"
#include "MockController.h"
#include "testutil.h"
#include "MockMode.h"

class RGBScreenTest : public ::testing::Test {
protected:

    MockController *controller;
    Screen *screen;
    MockMode *mode;

    virtual void SetUp() {
        controller = MockController::create();
        screen = new RGBScreen(controller);
        mode = new MockMode(controller, "Silly Mode");
        controller->setMode(mode);
    }

    virtual void TearDown() {
        delete screen;
        delete controller;
    }
};

TEST_F(RGBScreenTest, Hardcoding) {
    EXPECT_EQ("RGB", screen->getName());
}

//TEST_F(RGBScreenTest, Preview) {
//    controller->red = 9;
//    controller->green = 42;
//    controller->blue = 222;
//    screen->enter();
//
//    print_buffer(controller->display->getBuffer());
//}


