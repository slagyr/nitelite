#include <screen/SplashScreen.h>
#include <screen/RGBScreen.h>
#include <mode/YourColorMode.h>
#include "Controller.h"
#include "Context.h"
#include "math.h"

Controller::Controller() {
    lastUserEventTime = 0;
    splashScreen = new SplashScreen(this);
    rgbScreen = new RGBScreen(this);
    modes = new Mode*[10];
    modes[0] = new YourColorMode(this);
    tempScreenTimeout = 0;
}

void Controller::setup() {
    hardware->pinToInput(R_IN_PIN);
    hardware->pinToInput(G_IN_PIN);
    hardware->pinToInput(B_IN_PIN);
    hardware->pinToOutput(R_OUT_PIN);
    hardware->pinToOutput(G_OUT_PIN);
    hardware->pinToOutput(B_OUT_PIN);
    hardware->pinToOutput(OLED_PIN);
    setMode(modes[0]);
    setScreen(rgbScreen);
}

void Controller::setScreen(Screen *screen) {
    this->screen = screen;
    screen->enter();
}

Screen *Controller::getScreen() {
    return screen;
}

Screen *Controller::getActiveScreen() {
    if(tempScreen != nullptr)
        return tempScreen;
    return screen;
}

void Controller::setTempScreen(Screen *screen, int timeoutMillis) {
    tempScreen = screen;
    tempScreenTimeout = timeoutMillis;
    tempScreen->enter();
}

Mode *Controller::getMode() {
    return mode;
}

void Controller::setMode(Mode *m) {
    mode = m;
    mode->enter();
}

void Controller::tick(unsigned long millis) {
    getActiveScreen()->update();
    mode->tick();

    if (tempScreen != nullptr && millis > lastUserEventTime + tempScreenTimeout) {
        tempScreen = nullptr;
        screen->enter();
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

void Controller::readRGB() {
    int red = hardware->readAnalogPin(R_IN_PIN);
    int green = hardware->readAnalogPin(G_IN_PIN);
    int blue = hardware->readAnalogPin(B_IN_PIN);

    redInput = 1.0 * red / 1023  * 255;
    greenInput = 1.0 * green / 1023 * 255;
    blueInput = 1.0 * blue / 1023 * 255;
}

void Controller::writeRGB(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;

    hardware->analogWritePin(R_OUT_PIN, red);
    hardware->analogWritePin(G_OUT_PIN, green);
    hardware->analogWritePin(B_OUT_PIN, blue);
}

void Controller::writeRGBInputs() {
    writeRGB(redInput, greenInput, blueInput);
}
