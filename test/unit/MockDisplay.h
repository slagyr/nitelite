#ifndef NITELITE_MOCKDISPLAY_H
#define NITELITE_MOCKDISPLAY_H

#include <Display.h>

class MockDisplay : public Display {
public:
    void setup() override {
        wasSetup = true;
    }

    void splash() override {
        splashed = true;
    }

    void showHome() override {
        howmShown = true;
    }

    bool wasSetup = false;
    bool splashed;
    bool howmShown;
};

#endif
