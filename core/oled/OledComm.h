#ifndef OLEDCOMM_H
#define OLEDCOMM_H

#include "common.h"

class OledComm {
public:
    virtual void setup() = 0;

    virtual void sendCommand(byte cmd) = 0;

    virtual void sendData(const byte *data, int size) = 0;

    virtual void beginTransmission() = 0;

    virtual void includeByte(byte b) = 0;

    virtual void endTransmission() = 0;

    virtual byte pmgByte(const byte *bpm, int i) = 0;

    void setInverted(bool inverted) {
        OledComm::inverted = inverted;
    }

    bool isInverted() const {
        return inverted;
    }

protected:

    byte applyInversion(byte g) {
        return inverted ? ~g : g;
    }

private:
    bool inverted = false;
};

#endif
