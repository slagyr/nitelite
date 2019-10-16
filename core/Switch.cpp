#include "Switch.h"

Switch::Switch(Hardware *hardware, byte pin) : Switch(hardware, pin, true) {}

Switch::Switch(Hardware *hardware, byte pin, bool pullUp) {
    this->hardware = hardware;
    this->pin = pin;
    this->isPullUp = pullUp;
    currentlyOn = false;
}

void Switch::setup() {
    hardware->pinToOutput(pin);
}

void Switch::on() {
    if(isPullUp)
        hardware->setPinHigh(pin);
    else
        hardware->setPinLow(pin);
    currentlyOn = true;
}

void Switch::off() {
    if(isPullUp)
        hardware->setPinLow(pin);
    else
        hardware->setPinHigh(pin);
    currentlyOn = false;
}

bool Switch::isOn() {
    return currentlyOn;
}

byte Switch::getPin() const {
    return pin;
}

bool Switch::isIsPullUp() const {
    return isPullUp;
}

Hardware *Switch::getHardware() {
    return hardware;
}
