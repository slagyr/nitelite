#ifndef HARDWARE_H
#define HARDWARE_H

#include "common.h"

class Hardware {

public:
    virtual void pinToInput(byte pin) = 0;
    virtual void pinToInputPullup(byte pin) = 0;
    virtual void pinToOutput(byte pin) = 0;
    virtual int readDigitalPin(byte pin) = 0;
    virtual int readAnalogPin(byte pin) = 0;
    virtual unsigned long getMillis() = 0;
    virtual void setPinHigh(byte pin) = 0;
    virtual void setPinLow(byte pin) = 0;
    virtual void analogWritePin(byte pin, int value) = 0;
    virtual void playNote(byte pin, unsigned int frequency, unsigned long duration) = 0;

    virtual void sleep(unsigned long duration) = 0;

    virtual void print(const char *value) = 0;
    virtual void print(int value) = 0;
    virtual void print(float value) = 0;
    void println(const char *value);
    void println(int value);
    void println(float value);
    void printValue(char* label, int value);
};


#endif
