#ifndef NITELITE_MOCKCONTROLLER_H
#define NITELITE_MOCKCONTROLLER_H

#include <Controller.h>
#include "MockHardware.h"
#include "MockOledComm.h"

class MockController : public Controller {
public:

    static MockController *create() {
        Hardware *hardware = new MockHardware();
        Oled *display = new Oled(hardware, new MockOledComm());

        MockController *controller = new MockController();

        controller->hardware = hardware;
        controller->display = display;

        controller->setup();

        return controller;
    }

    MockController() : Controller() {}
};

#endif
