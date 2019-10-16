#include <Arduino.h>
#include <avr/pgmspace.h>
#include "common.h"
#include <Controller.h>
#include "OLEDDisplay.h"
#include "ArduinoHardware.h"
#include "I2cOledComm.h"
//#include "EEPROMConfig.h"

class HackDisplay : public Display {
public:
    void setup() override {

    }

    void splash() override {

    }

    void showHome() override {

    }

};

Display *display;
ArduinoHardware *hardware;
Controller *controller;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    controller = new Controller();
    controller->display = new OLEDDisplay();
//    controller->display = new HackDisplay();
    controller->hardware = new ArduinoHardware();
    controller->setup();
    controller->displayOn();
    controller->setScreen(controller->splashScreen);

    Serial.print("availableMemory(): ");
    Serial.println(availableMemory());
}

void loop() {
    controller->tick(millis());
}

//

//
//int down_state = HIGH;
//
//void print_color_output(int r, int g, int b);
//
//void print_color_input(int red, int green, int blue);
//
//void update_user_color();
//
//bool volatile do_up = false;
//
//void up_pressed(){
//    do_up = true;
//    Serial.print("up pressed");
//}
//
//void setup()
//{
//    Serial.begin(9600);
//    pinMode(R_IN_PIN, INPUT);
//    pinMode(G_IN_PIN, INPUT);
//    pinMode(B_IN_PIN, INPUT);
//    pinMode(R_OUT_PIN, OUTPUT);
//    pinMode(G_OUT_PIN, OUTPUT);
//    pinMode(B_OUT_PIN, OUTPUT);
//    pinMode(UP_PIN, INPUT_PULLUP);
//    pinMode(DOWN_PIN, INPUT_PULLUP);
//
//    attachInterrupt(digitalPinToInterrupt(UP_PIN), up_pressed, LOW);
//}
//
//
//
//void fade(int from, int to) {
//    for(int i = 0; i < 255; i++) {
//        analogWrite(from, i);
//        delay(5);
//        analogWrite(to, 255 - i);
//        delay(5);
//    }
//}
//
//void loop()
//{
//    if(do_up)
//        Serial.print("UP");
//
//    update_user_color();
//
//    do_up = false;
//
//    //    delay(10);
//}
//
//void update_user_color() {
//    int red = analogRead(R_IN_PIN);
//    int green = analogRead(G_IN_PIN);
//    int blue = analogRead(B_IN_PIN);
//
//    int r = red / 870.0 * 255;
//    int g = green / 870.0 * 255;
//    int b = blue / 870.0 * 255;
//
//    analogWrite(R_OUT_PIN, r);
//    analogWrite(G_OUT_PIN, g);
//    analogWrite(B_OUT_PIN, b);
//}
//
//void print_color_input(int red, int green, int blue) {
//    Serial.print("RGB in: ");
//    Serial.print(red);
//    Serial.print(", ");
//    Serial.print(green);
//    Serial.print(", ");
//    Serial.println(blue);
//}
//
//void print_color_output(int r, int g, int b) {
//    Serial.print("RGB out: ");
//    Serial.print(r);
//    Serial.print(", ");
//    Serial.print(g);
//    Serial.print(", ");
//    Serial.println(b);
//}
