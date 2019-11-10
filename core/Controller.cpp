#include <screen/SplashScreen.h>
#include <screen/RGBScreen.h>
#include <mode/YourColorMode.h>
#include <mode/YourBreathMode.h>
#include <mode/RGBFadeMode.h>
#include <mode/YourHeartbeatMode.h>
#include <mode/FireworksMode.h>
#include <mode/YourDiscoMode.h>
#include <mode/RGBDiscoMode.h>
#include <mode/WanderMode.h>
#include <mode/July4thMode.h>
#include <mode/TravelingMode.h>
#include <mode/RWBMode.h>
#include <mode/CalibrateMode.h>
#include <mode/HalloweenMode.h>
#include <mode/ChristmasMode.h>
#include <mode/SleepMode.h>
#include <mode/SettingsMode.h>
#include "Controller.h"
#include "math.h"

Controller *Controller::instance = nullptr;

Controller::Controller(Hardware *hardware) {
    this->hardware = hardware;

    splashScreen = new SplashScreen();
    rgbScreen = new RGBScreen();

    calibrateMode = new CalibrateMode();
    settingsMode = new SettingsMode();
    sleepMode = new SleepMode();
    modes = new Mode *[MODES]();
    modes[0] = new YourColorMode();
    modes[1] = new YourBreathMode();
    modes[2] = new YourHeartbeatMode();
    modes[3] = new YourDiscoMode();
    modes[4] = new RGBFadeMode();
    modes[5] = new FireworksMode();
    modes[6] = new July4thMode();
    modes[7] = new RGBDiscoMode();
    modes[8] = new WanderMode();
    modes[9] = new TravelingMode();
    modes[10] = new RWBMode();
    modes[11] = new HalloweenMode();
    modes[12] = new ChristmasMode();
    modeIndex = 0;

    config = new Config();
    upButton = new Button(hardware, UP_PIN);
    downButton = new Button(hardware, DOWN_PIN);

    lastUserEventTime = 0;
    tempScreenTimeout = 0;
    tempScreen = nullptr;
    isDisplayOn = false;
}

Controller::~Controller() {
    delete upButton;
    delete downButton;
}

void Controller::setup() {
    hardware->pinToInput(R_IN_PIN);
    hardware->pinToInput(G_IN_PIN);
    hardware->pinToInput(B_IN_PIN);
    hardware->pinToOutput(R_OUT_PIN);
    hardware->pinToOutput(G_OUT_PIN);
    hardware->pinToOutput(B_OUT_PIN);
    hardware->pinToOutput(OLED_PIN);

    setModeIndex(hardware->loadMode());
    setScreen(rgbScreen);
}

void Controller::setScreen(Screen *screen) {
    this->screen = screen;
    if (tempScreen == nullptr)
        screen->enter();
}

Screen *Controller::getActiveScreen() {
    if (tempScreen != nullptr)
        return tempScreen;
    return screen;
}

void Controller::setTempScreen(Screen *screen, int timeoutMillis) {
    tempScreen = screen;
    tempScreenTimeout = timeoutMillis;
    tempScreen->enter();
}

void Controller::setMode(Mode *m) {
    mode = m;
    mode->enter();
}

void Controller::tick(unsigned long millis) {
    if(isDisplayOn)
        getActiveScreen()->update();
    else
        hardware->sleep(65); // how long the screen update would have taken

    upButton->tick();
    downButton->tick();
    if (downButton->pressed())
        downPressed(millis);
    if (upButton->pressed())
        upPressed(millis);

    mode->tick();

    handleTempScreenTimeout(millis);
    handleScreenTimeout(millis);
    handleLightsTimeout(millis);
}

void Controller::handleLightsTimeout(unsigned long millis) {
    if (mode != sleepMode) {
        byte lTimeout = lightsTimeout();
        if (lTimeout <= LIGHTS_TIMEOUT_MAX && millis > (lastUserEventTime + lTimeout * 60000))
            setMode(sleepMode);
    }
}

void Controller::handleScreenTimeout(unsigned long millis) {
    if (isDisplayOn) {
        byte sTimeout = screenTimeout();
        if (sTimeout <= SCREEN_TIMEOUT_MAX && millis > (lastUserEventTime + sTimeout * 1000))
            displayOff();
    }
}

void Controller::handleTempScreenTimeout(unsigned long millis) {
    if (tempScreen != nullptr && millis > lastUserEventTime + tempScreenTimeout) {
        expireTempScreen();
        lastUserEventTime = millis;
    }
}

void Controller::downPressed(unsigned long millis) {
    lastUserEventTime = millis;
    if (tempScreen == splashScreen) {
        setMode(settingsMode);
        expireTempScreen();
    } else if(mode == sleepMode) {
        setModeIndex(modeIndex);
    } else
        setModeIndex(++modeIndex);
    displayOn();
}

void Controller::upPressed(unsigned long millis) {
    lastUserEventTime = millis;
    if (tempScreen == splashScreen) {
        setMode(calibrateMode);
        expireTempScreen();
    } else if(mode == sleepMode) {
        setModeIndex(modeIndex);
    } else
        setModeIndex(--modeIndex);
    displayOn();
}

void Controller::expireTempScreen() {
    tempScreen = nullptr;
    screen->enter();
}

void Controller::setModeIndex(short mode) {
    modeIndex = mode;
    if (modeIndex >= MODES)
        modeIndex = 0;
    if (modeIndex < 0)
        modeIndex = MODES - 1;
    hardware->saveMode(modeIndex);
    setMode(modes[modeIndex]);
}

void Controller::displayOn() {
    if (isDisplayOn)
        return;
    hardware->setPinHigh(OLED_PIN);
    hardware->sleep(100);
    display->setup();
    isDisplayOn = true;
    getActiveScreen()->enter();
}

void Controller::displayOff() {
    if (!isDisplayOn)
        return;
    display->clearScreen();
    hardware->setPinLow(OLED_PIN);
    isDisplayOn = false;
}

void Controller::readRGB() {
    int red = hardware->readAnalogPin(R_IN_PIN);
    int green = hardware->readAnalogPin(G_IN_PIN);
    int blue = hardware->readAnalogPin(B_IN_PIN);

    redInput = 255 - analogToDigitalColor(red, config->rMin, config->rMax);
    if (redInput <= 2)
        redInput = 0;
    greenInput = 255 - analogToDigitalColor(green, config->gMin, config->gMax);
    if (greenInput <= 2)
        greenInput = 0;
    blueInput = 255 - analogToDigitalColor(blue, config->bMin, config->bMax);
    if (blueInput <= 2)
        blueInput = 0;
}

byte Controller::analogToDigitalColor(int a, short min, short max) const {
    double value = 1.0 * (a - min) / (max - min) * 255;
    if (value > 255)
        value = 255;
    if (value < 0)
        value = 0;
    return (byte) value;
}

void Controller::writeRGB(byte r, byte g, byte b) {
    red = r;
    green = g;
    blue = b;
    writeRGB();
}

void Controller::writeRGB() const {
    hardware->analogWritePin(R_OUT_PIN, ftob(red));
    hardware->analogWritePin(G_OUT_PIN, ftob(green));
    hardware->analogWritePin(B_OUT_PIN, ftob(blue));
}

void Controller::writeRGBInputs() {
    writeRGB(redInput, greenInput, blueInput);
}

byte Controller::ftob(float color) const {
    if (color < 0)
        return 0;
    if (color > 254.5)
        return 255;
    return (byte) (color + 0.5);
}

//byte Controller::getRed() {
//    return ftob(red);
//}
//
//byte Controller::getGreen() {
//    return ftob(green);
//}
//
//byte Controller::getBlue() {
//    return ftob(blue);
//}
//
//void Controller::printRGB() {
//    hardware->print("RGB: ");
//    hardware->print(red);
//    hardware->print(", ");
//    hardware->print(green);
//    hardware->print(", ");
//    hardware->println(blue);
//}

void Controller::configDefaults() {
    config->screenTimeout = 255;
    config->lightsTimeout = 255;
    config->rMin = 0;
    config->rMax = 1023;
    config->gMin = 0;
    config->gMax = 1023;
    config->bMin = 0;
    config->bMax = 1023;
}

byte Controller::screenTimeout() {
    return (config->screenTimeout / TIMEOUT_DIVISOR + 1) * SCREEN_TIMEOUT_MULT;
}

byte Controller::lightsTimeout() {
    return (config->lightsTimeout / TIMEOUT_DIVISOR + 1) * LIGHTS_TIMEOUT_MULT;
}

