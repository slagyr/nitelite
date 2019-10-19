#include "ArduinoHardware.h"
#include "Arduino.h"
#include <EEPROM.h>

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
    return analogRead(pin);
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

void ArduinoHardware::print(int value) {
    Serial.print(value);
}

void ArduinoHardware::print(float value) {
    Serial.print(value);

}

void ArduinoHardware::saveConfig(Config *conf) {
    EEPROM.put(CONFIG_ADDRESS, *conf);
}

void ArduinoHardware::loadConfig(Config *conf) {
    EEPROM.get(CONFIG_ADDRESS, *conf);
}

byte ArduinoHardware::pmgByte(const byte *bmp, int i) {
    return pgm_read_byte(bmp + i);
}

