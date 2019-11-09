#include <gtest/gtest.h>
#include "screen/SplashScreen.h"
#include "MockController.h"
#include "testutil.h"

class SplashScreenTest : public ::testing::Test {
protected:

    MockController *controller;
    Screen *screen;

    virtual void SetUp() {
        controller = MockController::create();
        screen = new SplashScreen();
    }

    virtual void TearDown() {
        delete screen;
        delete controller;
    }
};

TEST_F(SplashScreenTest, Hardcoding) {
    EXPECT_EQ("Splash", screen->getName());
}

//TEST_F(SplashScreenTest, Preview) {
//    screen->enter();
//
//    print_buffer(controller->display->getBuffer());
//}

