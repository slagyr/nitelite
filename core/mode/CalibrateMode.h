#ifndef NITELITE_CALIBRATEMODE_H
#define NITELITE_CALIBRATEMODE_H

#include <Mode.h>

class CalibrateMode : public Mode {

public:

    CalibrateMode();

    const char *getName() override;

    void enter() override;

    void tick() override;

    Screen *configScreen;
};

#endif //NITELITE_CALIBRATEMODE_H
