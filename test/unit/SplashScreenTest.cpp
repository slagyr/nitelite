#include <gtest/gtest.h>
#include "screen/SplashScreen.h"
#include "MockController.h"

class SplashScreenTest : public ::testing::Test {
protected:

    MockController *controller;
    Screen *screen;

    virtual void SetUp() {
        controller = MockController::create();
        screen = new SplashScreen(controller);
    }

    virtual void TearDown() {
        delete screen;
        delete controller;
    }
};

TEST_F(SplashScreenTest, Hardcoding) {
    EXPECT_EQ("Splash", screen->getName());
    EXPECT_EQ(3000, screen->getIdleTimeout());
}

//TEST_F(SplashScreenTest, Enter) {
//    screen->enter();
//
//    EXPECT_EQ(true, controller->mockDisplay->splashed);
//}

