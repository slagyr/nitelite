#include <gtest/gtest.h>
#include "screen/RGBScreen.h"
#include "MockController.h"

class RGBScreenTest : public ::testing::Test {
protected:

    MockController *controller;
    Screen *screen;

    virtual void SetUp() {
        controller = MockController::create();
        screen = new RGBScreen(controller);
    }

    virtual void TearDown() {
        delete screen;
        delete controller;
    }
};

TEST_F(RGBScreenTest, Hardcoding) {
    EXPECT_EQ("RGB", screen->getName());
    EXPECT_EQ(3600000, screen->getIdleTimeout());
}

//TEST_F(RGBScreenTest, Enter) {
//    controller->hackVoltage(0, 3.0);
//    controller->hackVoltage(1, 3.1);
//    controller->hackVoltage(2, 3.2);
//    controller->hackVoltage(3, 3.3);
//    controller->hackVoltage(4, 3.4);
//    controller->hackVoltage(5, 3.5);
//    controller->hackVoltage(6, 3.6);
//    controller->hackVoltage(7, 3.7);
//    controller->hackVoltage(8, 3.8);
//    controller->hackVoltage(9, 3.9);
//
//    screen->enter();
//
//    EXPECT_NEAR(3.0, display->voltages[0], 0.01);
//    EXPECT_NEAR(3.1, display->voltages[1], 0.01);
//    EXPECT_NEAR(3.2, display->voltages[2], 0.01);
//    EXPECT_NEAR(3.3, display->voltages[3], 0.01);
//    EXPECT_NEAR(3.4, display->voltages[4], 0.01);
//    EXPECT_NEAR(3.5, display->voltages[5], 0.01);
//    EXPECT_NEAR(3.6, display->voltages[6], 0.01);
//    EXPECT_NEAR(3.7, display->voltages[7], 0.01);
//    EXPECT_NEAR(3.8, display->voltages[8], 0.01);
//    EXPECT_NEAR(3.9, display->voltages[9], 0.01);
//    EXPECT_EQ(true, display->howmShown);
//}

//TEST_F(RGBScreenTest, Update) {
//    controller->hackCurrentCell(6);
//    controller->hackCurrentCellVoltageChanged(true);
//    controller->hackVoltage(6, 3.0);
//
//    screen->update();
//
//    EXPECT_NEAR(3.0, display->voltages[6], 0.01);
//}
//
//TEST_F(RGBScreenTest, BalancingIndication) {
//    controller->hackBalancing(3, 6, true);
//
//    screen->update();
//
//    EXPECT_EQ(3, display->balanceToCell);
//    EXPECT_EQ(6, display->balanceFromCell);
//    EXPECT_EQ(true, display->balancingIndicated);
//}


