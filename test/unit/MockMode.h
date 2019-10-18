#ifndef NITELITE_MOCKMODE_H
#define NITELITE_MOCKMODE_H

#include <Controller.h>

class MockMode : public Mode {
public:

    MockMode(Controller *controller, const char* name) : Mode(controller) {
        this->name = name;
    }

    const char *getName() override {
        return name;
    }

    void enter() override {
        wasEntered = true;
    }

    void tick() override {
        wasTicked = true;
    }

    bool wasEntered = false;
    bool wasTicked = false;
    const char *name;
};

#endif //NITELITE_MOCKMODE_H
