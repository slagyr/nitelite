#include "Button.h"

Button::Button(Hardware* hardware, byte pin) {
    this->hardware = hardware;
    _pin = pin;
    _pressed = false;
    _previous = false;
}

byte Button::pin() {
    return _pin;
}

bool Button::pressed() {
    if(_pressed) {
        _pressed = false;
        return true;
    }
    else
        return false;
}

void Button::tick() {
    int v = hardware->readDigitalPin(_pin);
    if(v == 0 && !_previous) {
        _pressed = true;
        _previous = true;
    }
    else if(v != 0)
        _previous = false;
}

bool Button::isDown() {
    return hardware->readDigitalPin(_pin) == 0;
}

void Button::force(bool pressed) {
    _pressed = pressed;
}
