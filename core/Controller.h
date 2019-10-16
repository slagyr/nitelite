#ifndef NITELITE_CONTROLLER_H
#define NITELITE_CONTROLLER_H

#include "Hardware.h"
#include "Display.h"
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

    void setMode(Mode *m);

    Screen *getScreen();

    Mode *getMode();

    void displayOn();

    void displayOff();

    void readRGB();

    void writeRGB(int r, int g, int b);

    void writeRGBInputs();


    Screen *splashScreen;
    Screen *rgbScreen;

    LinkedList<Mode *> *modes;

    Hardware *hardware;
    Display *display;

    int redInput;
    int greenInput;
    int blueInput;
    int red;
    int green;
    int blue;


protected:

    Screen *screen;
    Mode *mode;

private:

    unsigned long lastUserEventTime;

};


#endif //NITELITE_CONTROLLER_H
