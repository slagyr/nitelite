#define PROGMEM

#include <gtest/gtest.h>
#include <oled/OledFonts.h>
#include "oled/Oled.h"
#include "MockOledComm.h"

class OledTest : public ::testing::Test {
protected:

    MockOledComm *comm;
    Oled *oled;

    virtual void SetUp() {
        comm = new MockOledComm();
        oled = new Oled(comm);
    }

    virtual void TearDown() {
        delete comm;
        delete oled;
    }
};

TEST_F(OledTest, Creation) {
    EXPECT_EQ(comm, oled->getComm());
}

TEST_F(OledTest, Setup) {
    oled->setup();

    EXPECT_EQ(true, comm->wasSetup);
    EXPECT_NE(0, comm->commands->size());
}

TEST_F(OledTest, BitmapFullScreen) {
    byte bmp[1024];
    for(int i = 0; i < 1024; i++)
        bmp[i] = 0x42;

    oled->drawBitmap(0, 0, 128, 64, bmp);

    EXPECT_EQ(0x21, comm->commands->shift());
    EXPECT_EQ(0, comm->commands->shift());
    EXPECT_EQ(127, comm->commands->shift());
    EXPECT_EQ(0x22, comm->commands->shift());
    EXPECT_EQ(0, comm->commands->shift());
    EXPECT_EQ(7, comm->commands->shift());

    EXPECT_EQ(1024, comm->transmission->size());
    for(int i = 0; i < 1024; i++)
        EXPECT_EQ(0x42, comm->transmission->get(i));
}

TEST_F(OledTest, BitmapQuarterScreen) {
    byte bmp[256];
    for(int i = 0; i < 256; i++)
        bmp[i] = 0x42;

    oled->drawBitmap(32, 2, 64, 32, bmp);

    EXPECT_EQ(0x21, comm->commands->shift());
    EXPECT_EQ(32, comm->commands->shift());
    EXPECT_EQ(95, comm->commands->shift());
    EXPECT_EQ(0x22, comm->commands->shift());
    EXPECT_EQ(2, comm->commands->shift());
    EXPECT_EQ(5, comm->commands->shift());

    EXPECT_EQ(256, comm->transmission->size());
    for(int i = 0; i < 256; i++)
        EXPECT_EQ(0x42, comm->transmission->get(i));
}


TEST_F(OledTest, ClearScreen) {
    oled->clearScreen();

    EXPECT_EQ(0x21, comm->commands->shift());
    EXPECT_EQ(0, comm->commands->shift());
    EXPECT_EQ(127, comm->commands->shift());
    EXPECT_EQ(0x22, comm->commands->shift());
    EXPECT_EQ(0, comm->commands->shift());
    EXPECT_EQ(7, comm->commands->shift());

    EXPECT_EQ(1024, comm->transmission->size());
    for(int i = 0; i < 1024; i++)
        EXPECT_EQ(0, comm->transmission->get(i));
}

TEST_F(OledTest, DefaultFont) {
    oled->setup();

    EXPECT_EQ(6, oled->getFontWidth());
}

TEST_F(OledTest, SetFont) {
    oled->setFont(oled_font5x7);

    EXPECT_EQ(5, oled->getFontWidth());
}

TEST_F(OledTest, WriteString) {
    oled->setFont(oled_font6x8);
    oled->writeString(42, 3, "Hello");

    EXPECT_EQ(0x21, comm->commands->shift());
    EXPECT_EQ(42, comm->commands->shift());
    EXPECT_EQ(71, comm->commands->shift());
    EXPECT_EQ(0x22, comm->commands->shift());
    EXPECT_EQ(3, comm->commands->shift());
    EXPECT_EQ(3, comm->commands->shift());

    EXPECT_EQ(30, comm->transmission->size());
    // H
    EXPECT_EQ(0, comm->transmission->shift());
    EXPECT_EQ(0x7F, comm->transmission->shift());
    EXPECT_EQ(0x08, comm->transmission->shift());
    EXPECT_EQ(0x08, comm->transmission->shift());
    EXPECT_EQ(0x08, comm->transmission->shift());
    EXPECT_EQ(0x7F, comm->transmission->shift());
    // e
    EXPECT_EQ(0, comm->transmission->shift());
    EXPECT_EQ(0x38, comm->transmission->shift());
    EXPECT_EQ(0x54, comm->transmission->shift());
    EXPECT_EQ(0x54, comm->transmission->shift());
    EXPECT_EQ(0x54, comm->transmission->shift());
    EXPECT_EQ(0x18, comm->transmission->shift());
}

TEST_F(OledTest, Clear) {
    oled->clear(12, 3, 24, 3);

    EXPECT_EQ(0x21, comm->commands->shift());
    EXPECT_EQ(12, comm->commands->shift());
    EXPECT_EQ(35, comm->commands->shift());
    EXPECT_EQ(0x22, comm->commands->shift());
    EXPECT_EQ(3, comm->commands->shift());
    EXPECT_EQ(5, comm->commands->shift());

    EXPECT_EQ(72, comm->transmission->size());
    for(int i = 0; i < 72; i++)
        EXPECT_EQ(0, comm->transmission->get(i));
}

TEST_F(OledTest, InvertedText) {
    oled->setFont(oled_font6x8);

    EXPECT_EQ(false, oled->isInverted());
    oled->setInverted(true);
    EXPECT_EQ(true, oled->isInverted());

    oled->writeString(42, 3, "Hello");

    EXPECT_EQ(30, comm->transmission->size());
    // H
    EXPECT_EQ(0xFF, comm->transmission->shift());
    EXPECT_EQ(0x80, comm->transmission->shift());
    EXPECT_EQ(0xF7, comm->transmission->shift());
    EXPECT_EQ(0xF7, comm->transmission->shift());
    EXPECT_EQ(0xF7, comm->transmission->shift());
    EXPECT_EQ(0x80, comm->transmission->shift());
    // e
    EXPECT_EQ(0xFF, comm->transmission->shift());
    EXPECT_EQ(0xC7, comm->transmission->shift());
    EXPECT_EQ(0xAB, comm->transmission->shift());
    EXPECT_EQ(0xAB, comm->transmission->shift());
    EXPECT_EQ(0xAB, comm->transmission->shift());
    EXPECT_EQ(0xE7, comm->transmission->shift());
}