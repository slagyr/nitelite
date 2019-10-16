#ifndef NITELITE_I2COLEDCOMM_H
#define NITELITE_I2COLEDCOMM_H

#include <oled/OledComm.h>
#include <Wire.h>


class I2cOledComm : public OledComm {
public:
    I2cOledComm();

    void setup() override;

    void sendCommand(byte cmd) override;

    void sendData(const byte *data, int size) override;

    void beginTransmission() override;

    void includeByte(byte b) override;

    void endTransmission() override;

    byte pmgByte(const byte *bmp, int i) override;

private:
    byte packetSize;
};


#endif
