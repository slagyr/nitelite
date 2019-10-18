#include <gtest/gtest.h>
#include <oled/OledFonts.h>
#include "oled/Oled.h"
#include "MockOledComm.h"
#include "testutil.h"

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
    oled->show();

    EXPECT_EQ(0x21, comm->commands->shift());
    EXPECT_EQ(0, comm->commands->shift());
    EXPECT_EQ(127, comm->commands->shift());
    EXPECT_EQ(0x22, comm->commands->shift());
    EXPECT_EQ(0, comm->commands->shift());
    EXPECT_EQ(7, comm->commands->shift());

//    print_buffer(oled->getBuffer());

    EXPECT_EQ(1024, comm->transmission->size());
    for(int i = 0; i < 1024; i++)
        EXPECT_EQ(0x42, comm->transmission->get(i));
}

TEST_F(OledTest, BitmapQuarterScreen) {
    byte bmp[256];
    for(int i = 0; i < 256; i++)
        bmp[i] = 0x42;

    oled->drawBitmap(32, 2, 64, 32, bmp);
    oled->show(32, 2, 64, 32);

//    print_buffer(oled->getBuffer());

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
    oled->clear();

    for(int i = 0; i < 1024; i++)
        EXPECT_EQ(0, oled->getBuffer()[i]);
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

    // H
    EXPECT_EQ(0x00, oled->getBuffer()[426]);
    EXPECT_EQ(0x7F, oled->getBuffer()[427]);
    EXPECT_EQ(0x08, oled->getBuffer()[428]);
    EXPECT_EQ(0x08, oled->getBuffer()[429]);
    EXPECT_EQ(0x08, oled->getBuffer()[430]);
    EXPECT_EQ(0x7F, oled->getBuffer()[431]);
    // e
    EXPECT_EQ(0x00, oled->getBuffer()[432]);
    EXPECT_EQ(0x38, oled->getBuffer()[433]);
    EXPECT_EQ(0x54, oled->getBuffer()[434]);
    EXPECT_EQ(0x54, oled->getBuffer()[435]);
    EXPECT_EQ(0x54, oled->getBuffer()[436]);
    EXPECT_EQ(0x18, oled->getBuffer()[437]);
}

TEST_F(OledTest, InvertedText) {
    oled->setFont(oled_font6x8);

    EXPECT_EQ(false, oled->isTextInverted());
    oled->setTextInverted(true);
    EXPECT_EQ(true, oled->isTextInverted());

    oled->writeString(42, 3, "Hello");

    // H
    EXPECT_EQ(0xFF, oled->getBuffer()[426]);
    EXPECT_EQ(0x80, oled->getBuffer()[427]);
    EXPECT_EQ(0xF7, oled->getBuffer()[428]);
    EXPECT_EQ(0xF7, oled->getBuffer()[429]);
    EXPECT_EQ(0xF7, oled->getBuffer()[430]);
    EXPECT_EQ(0x80, oled->getBuffer()[431]);
    // e
    EXPECT_EQ(0xFF, oled->getBuffer()[432]);
    EXPECT_EQ(0xC7, oled->getBuffer()[433]);
    EXPECT_EQ(0xAB, oled->getBuffer()[434]);
    EXPECT_EQ(0xAB, oled->getBuffer()[435]);
    EXPECT_EQ(0xAB, oled->getBuffer()[436]);
    EXPECT_EQ(0xE7, oled->getBuffer()[437]);
}