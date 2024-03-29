#ifndef HARDWARE_H
#define HARDWARE_H

#include "core.h"

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
    virtual void saveConfig(Config *conf) = 0;
    virtual void loadConfig(Config *conf) = 0;
    virtual void saveMode(byte mode) = 0;
    virtual byte loadMode() = 0;
    virtual long randomLong(long max) = 0;
    virtual byte pmgByte(const byte *bmp, int i) = 0;
    virtual void sleep(unsigned long duration) = 0;
    virtual void print(const char *value) = 0;
    virtual void print(long value) = 0;
    virtual void print(double value) = 0;
    void println(const char *value);
    void println(long value);
    void println(double value);
    void printValue(char* label, int value);

};


#endif
