#include <Arduino.h>
#include <avr/pgmspace.h>
#include "core.h"
#include <Controller.h>
#include <mode/CalibrateMode.h>
#include "ArduinoHardware.h"
#include "I2cOledComm.h"
#include "Button.h"

void setup() {
    Serial.begin(9600);
    while (!Serial);
    randomSeed(analogRead(0));

    pinMode(UP_PIN, INPUT_PULLUP);
    pinMode(DOWN_PIN, INPUT_PULLUP);

    Hardware *hardware = new ArduinoHardware();
    Controller *controller = new Controller(hardware);
    Controller::instance = controller;
    I2cOledComm *oledComm = new I2cOledComm();
    controller->display = new Oled(controller->hardware, oledComm);
    controller->setup();
    controller->displayOn();
    controller->setTempScreen(controller->splashScreen, 3000);

    hardware->loadConfig(controller->config);

    Serial.print("availableMemory(): ");
    Serial.println(availableMemory());
}

void loop() {
    Controller::instance->tick(millis());
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
//        analogWritePin(from, i);
//        delay(5);
//        analogWritePin(to, 255 - i);
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
