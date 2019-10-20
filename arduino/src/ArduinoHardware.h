#ifndef ARDUINOHARDWARE_H
#define ARDUINOHARDWARE_H


#include <Hardware.h>

class ArduinoHardware : public Hardware {

public:
    void pinToInput(byte pin) override;

    void pinToOutput(byte pin) override;

    int readDigitalPin(byte pin) override;

    int readAnalogPin(byte pin) override;

    unsigned long getMillis() override;

    void setPinHigh(byte pin) override;

    void setPinLow(byte pin) override;

    void print(const char *value) override;

    void print(long value) override;

    void print(double value) override;

    void playNote(byte pin, unsigned int frequency, unsigned long duration) override;

    void sleep(unsigned long duration) override;

    void pinToInputPullup(byte pin) override;

    void analogWritePin(byte pin, int value) override;

    void saveConfig(Config *conf) override;

    void loadConfig(Config *conf) override;

    byte pmgByte(const byte *bmp, int i) override;

    long randomLong(long max) override;
};


#endif //ARDUINOHARDWARE_H
