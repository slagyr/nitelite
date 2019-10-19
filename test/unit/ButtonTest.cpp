#include <gtest/gtest.h>
#include "Button.h"
#include "MockHardware.h"

class ButtonTest : public ::testing::Test {
protected:

    MockHardware *hardware;
    Button* button;

    virtual void SetUp() {
        hardware = new MockHardware();
        button = new Button(hardware, 6);
    }

    virtual void TearDown() {
        delete button;
        delete hardware;
    }
};

TEST_F(ButtonTest, Pin) {
    EXPECT_EQ(6, button->pin());
}

TEST_F(ButtonTest, InitialState) {
    EXPECT_EQ(false, button->pressed());
}

TEST_F(ButtonTest, Pressed) {
    hardware->digitalReads[6].push(0);
    button->tick();

    EXPECT_EQ(true, button->pressed());
}

TEST_F(ButtonTest, PressIsTemporary) {
    hardware->digitalReads[6].push(0);
    hardware->digitalReads[6].push(0);

    button->tick();
    EXPECT_EQ(true, button->pressed());

    button->tick();
    EXPECT_EQ(false, button->pressed());
}

TEST_F(ButtonTest, SecondPress) {
    hardware->digitalReads[6].push(0);
    hardware->digitalReads[6].push(1);
    hardware->digitalReads[6].push(0);

    button->tick();
    EXPECT_EQ(true, button->pressed());

    button->tick();
    EXPECT_EQ(false, button->pressed());

    button->tick();
    EXPECT_EQ(true, button->pressed());
}



