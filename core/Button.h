#ifndef NITELITE_BUTTON_H
#define NITELITE_BUTTON_H


#include "common.h"
#include "Hardware.h"

class Button {

public:
    byte _pin;

    Button(Hardware *hardware, byte pin);
    byte pin();
    bool pressed();
    bool isDown();
    void tick();
    void force(bool pressed);

private:
    Hardware* hardware;
    bool _pressed;
    bool _previous;
};


#endif //NITELITE_BUTTON_H
