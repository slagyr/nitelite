#ifndef NITELITE_MOCKOLEDCOMM_H
#define NITELITE_MOCKOLEDCOMM_H

#include <oled/OledComm.h>
#include <LinkedList.h>
#include <iostream>
using namespace std;

class MockOledComm : public OledComm {
public:
    MockOledComm() {
        commands = new LinkedList<byte>();
        transmission = new LinkedList<byte>();
    }

    void setup() override {
        wasSetup = true;
    }

    void sendCommand(byte cmd) override {
        commands->add(cmd);
    }

    void sendData(const byte *data, int size) override {
        transmission->clear();
        for(int i = 0; i < size; i++)
            includeByte(data[i]);
    }

    void beginTransmission() override {
        transmission->clear();
        inTransmission = true;
    }

    void includeByte(byte b) override {
        transmission->add(applyInversion(b));
    }

    void endTransmission() override {
        inTransmission = false;
    }

    byte pmgByte(const byte *bmp, int i) override {
        return bmp[i];
    }

    bool wasSetup;
    LinkedList<byte> *commands;
    LinkedList<byte> *transmission;
    bool inTransmission;
};

#endif //NITELITE_MOCKOLEDCOMM_H
