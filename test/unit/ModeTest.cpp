#include <gtest/gtest.h>
#include "Mode.h"
#include "MockController.h"
#include "MockMode.h"

class ModeTest : public ::testing::Test {
protected:

    Controller* controller;
    MockMode* mode;

    virtual void SetUp() {
        controller = MockController::create();
        mode = new MockMode(controller, "Blah");
    }

    virtual void TearDown() {
        delete mode;
        delete controller;
    }
};

TEST_F(ModeTest, FadeRedDown) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(-1, 0, 0, 0, 0, 0);

    EXPECT_EQ(false, result);
    EXPECT_EQ(99, controller->red);
    EXPECT_EQ(100, controller->green);
    EXPECT_EQ(100, controller->blue);
}

TEST_F(ModeTest, FadeAllDown) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(-1, -1, -1, 0, 0, 0);

    EXPECT_EQ(false, result);
    EXPECT_EQ(99, controller->red);
    EXPECT_EQ(99, controller->green);
    EXPECT_EQ(99, controller->blue);
}

TEST_F(ModeTest, FadeAllUp) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(1, 1, 1, 255, 255, 255);

    EXPECT_EQ(false, result);
    EXPECT_EQ(101, controller->red);
    EXPECT_EQ(101, controller->green);
    EXPECT_EQ(101, controller->blue);
}

TEST_F(ModeTest, FadeDownToRedLimit) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(-1, -1, -1, 99, 0, 0);

    EXPECT_EQ(true, result);
}

TEST_F(ModeTest, FadeDownToGreenLimit) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(-1, -1, -1, 0, 99, 0);

    EXPECT_EQ(true, result);
}

TEST_F(ModeTest, FadeDownToBlueLimit) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(-1, -1, -1, 0, 0, 99);

    EXPECT_EQ(true, result);
}

TEST_F(ModeTest, FadeUpToRedLimit) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(1, 1, 1, 101, 255, 255);

    EXPECT_EQ(true, result);
}

TEST_F(ModeTest, FadeUpToGreenLimit) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(1, 1, 1, 255, 101, 255);

    EXPECT_EQ(true, result);
}

TEST_F(ModeTest, FadeUpToBlueLimit) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(1, 1, 1, 255, 255, 101);

    EXPECT_EQ(true, result);
}

TEST_F(ModeTest, FadeNotTooHigh) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(200, 200, 200, 255, 255, 101);

    EXPECT_EQ(true, result);
    EXPECT_EQ(255, controller->red);
    EXPECT_EQ(255, controller->green);
    EXPECT_EQ(101, controller->blue);
}

TEST_F(ModeTest, FadeNotTooLow) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(-200, -200, -200, 0, 0, 0);

    EXPECT_EQ(true, result);
    EXPECT_EQ(0, controller->red);
    EXPECT_EQ(0, controller->green);
    EXPECT_EQ(0, controller->blue);
}

TEST_F(ModeTest, FadeNotPastLimitHigh) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(100, 100, 100, 150, 150, 150);

    EXPECT_EQ(true, result);
    EXPECT_EQ(150, controller->red);
    EXPECT_EQ(150, controller->green);
    EXPECT_EQ(150, controller->blue);
}

TEST_F(ModeTest, FadeNotPastLimitLow) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    bool result = mode->fade(-100, -100, -100, 50, 50, 50);

    EXPECT_EQ(true, result);
    EXPECT_EQ(50, controller->red);
    EXPECT_EQ(50, controller->green);
    EXPECT_EQ(50, controller->blue);
}

TEST_F(ModeTest, FadeDownToLimitFractionally) {
    controller->red = 100;
    controller->green = 100;
    controller->blue = 100;

    mode->fade(-1, -1, -0.79, 0, 0, 99);
    bool result = mode->fade(-1, -1, -0.79, 0, 0, 99);

    EXPECT_EQ(true, result);
    EXPECT_EQ(99, controller->blue);
}

//TEST_F(ModeTest, RandomColor) {
//    Color c;
//
//    mode->randomColor(&c);
//
//    cout << (int)c.r << endl;
//    cout << (int)c.g << endl;
//    cout << (int)c.b << endl;
//}
//
//TEST_F(ModeTest, RandomBrightColor) {
//    Color c;
//
//    mode->randomBrightColor(&c);
//
//    cout << (int)c.r << endl;
//    cout << (int)c.g << endl;
//    cout << (int)c.b << endl;
//}


