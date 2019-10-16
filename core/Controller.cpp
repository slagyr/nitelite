#include <screen/SplashScreen.h>
#include <screen/HomeScreen.h>
#include "Controller.h"
#include "Context.h"
#include "math.h"

Controller::Controller() {
    lastUserEventTime = 0;
    splashScreen = new SplashScreen(this);
    homeScreen = new HomeScreen(this);
}

void Controller::setup() {

    hardware->pinToInput(R_IN_PIN);
    hardware->pinToInput(G_IN_PIN);
    hardware->pinToInput(B_IN_PIN);
    hardware->pinToOutput(R_OUT_PIN);
    hardware->pinToOutput(G_OUT_PIN);
    hardware->pinToOutput(B_OUT_PIN);
    hardware->pinToOutput(OLED_PIN);
}

void Controller::setScreen(Screen *screen) {
    this->screen = screen;
    screen->enter();
}

Screen *Controller::getScreen() {
    return screen;
}

void Controller::tick(unsigned long millis) {
    screen->update();

    if (millis > lastUserEventTime + screen->getIdleTimeout()) {
        setScreen(homeScreen);
        lastUserEventTime = millis;
    }
}

void Controller::displayOn() {
    hardware->setPinHigh(OLED_PIN);
    hardware->sleep(100);
    display->setup();
}

void Controller::displayOff() {
    hardware->setPinLow(OLED_PIN);
}
