#ifndef VOLTAGEALARM_SWITCH_H
#define VOLTAGEALARM_SWITCH_H


#include "Hardware.h"

class Switch {

public:
    Switch(Hardware *hardware, byte pin);
    Switch(Hardware *hardware, byte pin, bool pullUp);

    virtual void setup();
    byte getPin() const;

    virtual void on();

    virtual void off();
    bool isOn();
    bool isIsPullUp() const;
    Hardware* getHardware();

private:

    bool currentlyOn;
    bool isPullUp;
    Hardware *hardware;
    byte pin;
};


#endif //VOLTAGEALARM_SWITCH_H
