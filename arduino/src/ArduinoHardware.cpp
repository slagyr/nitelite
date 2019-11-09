#include "ArduinoHardware.h"
#include "Arduino.h"
#include <EEPROM.h>


#define MODE_ADDRESS 42
#define CALIBRATION_ADDRESS 100

void ArduinoHardware::pinToInput(byte pin) {
    pinMode(pin, INPUT);
}

void ArduinoHardware::pinToInputPullup(byte pin) {
    pinMode(pin, INPUT_PULLUP);
}

void ArduinoHardware::pinToOutput(byte pin) {
    pinMode(pin, OUTPUT);

}

int ArduinoHardware::readDigitalPin(byte pin) {
    return digitalRead(pin);
}

int ArduinoHardware::readAnalogPin(byte pin) {
    int total = 0;
    for(int i = 0; i < 10; i++){
        total += analogRead(pin);
    }
    return total / 10;
}

unsigned long ArduinoHardware::getMillis() {
    return millis();
}

void ArduinoHardware::setPinHigh(byte pin) {
    digitalWrite(pin, HIGH);
}

void ArduinoHardware::setPinLow(byte pin) {
    digitalWrite(pin, LOW);
}

void ArduinoHardware::analogWritePin(byte pin, int value) {
    analogWrite(pin, value);
}

void ArduinoHardware::playNote(byte pin, unsigned int frequency, unsigned long duration) {
    tone(pin, frequency, duration);
}

void ArduinoHardware::sleep(unsigned long duration) {
    delay(duration);
}

void ArduinoHardware::print(const char *value) {
    Serial.print(value);
}

void ArduinoHardware::print(long value) {
    Serial.print(value);
}

void ArduinoHardware::print(double value) {
    Serial.print(value);
}

void ArduinoHardware::saveCalibration(Config *conf) {
    EEPROM.put(CALIBRATION_ADDRESS, *conf);
}

void ArduinoHardware::loadCalibration(Config *conf) {
    EEPROM.get(CALIBRATION_ADDRESS, *conf);
}

void ArduinoHardware::saveMode(byte mode) {
    EEPROM.put(MODE_ADDRESS, mode);
}

byte ArduinoHardware::loadMode() {
    byte mode;
    return EEPROM.get(MODE_ADDRESS, mode);
}

byte ArduinoHardware::pmgByte(const byte *bmp, int i) {
    return pgm_read_byte(bmp + i);
}

long ArduinoHardware::randomLong(long max) {
    return random(max);
}

