#ifndef NITELITE_CONTROLLER_H
#define NITELITE_CONTROLLER_H

#include "Hardware.h"
#include "oled/Oled.h"
#include "Screen.h"
#include "core.h"
#include "Mode.h"
#include "LinkedList.h"
#include "Button.h"

#define MODES 13

class Controller {

public:
    Controller(Hardware *hardware);
    ~Controller();

    void setup();

    void tick(unsigned long millis);

    void setScreen(Screen *screen);

    void setTempScreen(Screen *screen, int timeoutMillis);

    void setMode(Mode *m);

    Screen *getActiveScreen();

    void configDefaults();

    void displayOn();

    void displayOff();

    void readRGB();

    void writeRGB(byte r, byte g, byte b);

    void writeRGB() const;

    void writeRGBInputs();

    void setModeIndex(short mode);

    void expireTempScreen();

    byte screenTimeout();
    byte lightsTimeout();

//    byte getRed();
//
//    byte getGreen();
//
//    byte getBlue();
//
//    void printRGB();

    static Controller *instance;

    Screen *screen;
    Screen *splashScreen;
    Screen *rgbScreen;
    Screen *tempScreen;

    Mode *mode;
    Mode **modes;
    Mode *calibrateMode;
    Mode *settingsMode;
    Mode *sleepMode;

    Hardware *hardware;
    Oled *display;
    Config *config;
    Button *upButton;
    Button *downButton;

    byte redInput;
    byte greenInput;
    byte blueInput;
    float red;
    float green;
    float blue;
    short tempScreenTimeout;
    short modeIndex;
    unsigned long lastUserEventTime;
    bool isDisplayOn;

private:


    byte analogToDigitalColor(int a, short min, short max) const;

    byte ftob(float red) const;

    void upPressed(unsigned long millis);

    void downPressed(unsigned long millis);

    void handleTempScreenTimeout(unsigned long millis);

    void handleScreenTimeout(unsigned long millis);

    void handleLightsTimeout(unsigned long millis);
};


#endif //NITELITE_CONTROLLER_H
