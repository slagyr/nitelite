#ifndef NITELITE_MOCKSCREEN_H
#define NITELITE_MOCKSCREEN_H

#include <Screen.h>

class MockScreen : public Screen {
public:
    MockScreen(Controller *controller) : MockScreen(controller, "Mock Screen") {}
    MockScreen(Controller *controller, const char* name) : Screen() {
        this->name = name;
    }

    const char *getName() override {
        return name;
    }

    void enter() override {
        wasEntered = true;
    }

    void update() override {
        wasUpdated = true;
    }

    bool wasEntered = false;
    bool wasUpdated = false;
    const char *name;
    unsigned long timeout = 6000;
};

#endif //NITELITE_MOCKSCREEN_H
