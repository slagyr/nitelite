#ifndef NITELITE_MOCKCONTROLLER_H
#define NITELITE_MOCKCONTROLLER_H

#include <Controller.h>
#include "MockDisplay.h"
#include "MockHardware.h"

class MockController : public Controller {
public:

    MockDisplay *mockDisplay;

    static MockController *create() {
        Hardware *hardware = new MockHardware();
        MockDisplay *display = new MockDisplay();

        MockController *controller = new MockController();

        controller->hardware = hardware;
        controller->display = display;

        return controller;
    }

    MockController() : Controller() {}
};

#endif
