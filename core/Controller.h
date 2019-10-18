#ifndef NITELITE_CONTROLLER_H
#define NITELITE_CONTROLLER_H

#include "Hardware.h"
#include "oled/Oled.h"
#include "Screen.h"
#include "Switch.h"
#include "Context.h"
#include "Mode.h"
#include "LinkedList.h"

class Controller {

public:
    Controller();

    void setup();

    void tick(unsigned long millis);

    void setScreen(Screen *screen);

    void setTempScreen(Screen *screen, int timeoutMillis);

    void setMode(Mode *m);

    Screen *getScreen();
    Screen *getActiveScreen();

    Mode *getMode();

    void displayOn();

    void displayOff();

    void readRGB();

    void writeRGB(int r, int g, int b);

    void writeRGBInputs();


    Screen *splashScreen;
    Screen *rgbScreen;

    Mode **modes;

    Hardware *hardware;
    Oled *display;

    byte redInput;
    byte greenInput;
    byte blueInput;
    byte red;
    byte green;
    byte blue;
    short tempScreenTimeout;


protected:

    Screen *screen;
    Screen *tempScreen;
    Mode *mode;

private:

    unsigned long lastUserEventTime;

};


#endif //NITELITE_CONTROLLER_H
