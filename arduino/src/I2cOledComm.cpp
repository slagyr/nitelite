#include <HardwareSerial.h>
#include "I2cOledComm.h"

#define SSD1306_ADDRESS 0x3C
#define SSD1306_COMMAND 0x00
#define SSD1306_DATA 0x40

#define SSD1306_PACKET_SIZE 30

I2cOledComm::I2cOledComm() {
    packetSize = 0;
}

void I2cOledComm::setup() {
    Wire.begin();
}

void I2cOledComm::sendCommand(byte cmd) {
    Wire.beginTransmission(SSD1306_ADDRESS);
    Wire.write(SSD1306_COMMAND);
    Wire.write(cmd);
    Wire.endTransmission();
}

void I2cOledComm::sendData(const byte *data, int size) {
    beginTransmission();
    for(int i = 0; i < size; i++)
        includeByte(data[i]);
    endTransmission();
}

void I2cOledComm::beginTransmission() {
    packetSize = 0;
    Wire.beginTransmission(SSD1306_ADDRESS);
    Wire.write(SSD1306_DATA);
}

void I2cOledComm::includeByte(byte b) {
    if(packetSize == SSD1306_PACKET_SIZE) {
        Wire.endTransmission();
        packetSize = 0;
        Wire.beginTransmission(SSD1306_ADDRESS);
        Wire.write(SSD1306_DATA);
    }
    Wire.write(applyInversion(b));
    packetSize++;
}

void I2cOledComm::endTransmission() {
    Wire.endTransmission();
}

byte I2cOledComm::pmgByte(const byte *bmp, int i) {
    return pgm_read_byte(bmp + i);
}
