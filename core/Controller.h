#ifndef NITELITE_CONTROLLER_H
#define NITELITE_CONTROLLER_H

#include "Hardware.h"
#include "Display.h"
#include "Screen.h"
#include "Switch.h"
#include "Context.h"

#define CELL_COUNT 10

class Controller {

public:
    Controller();

    void setup();

    void tick(unsigned long millis);

    void setScreen(Screen *screen);

    Screen* getScreen();

    // Screens
    Screen *splashScreen;
    Screen *homeScreen;

    Hardware *hardware;
    Display *display;
    Switch *fetSwitch;
    Switch *capSwitch;
    Switch *balanceSwitch;

    void displayOn();

    void displayOff();

protected:

    Screen* screen;

private:

    unsigned long lastUserEventTime;

};


#endif //NITELITE_CONTROLLER_H
