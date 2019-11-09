#ifndef NITELITE_SLEEPMODE_H
#define NITELITE_SLEEPMODE_H


#include <Mode.h>

class SleepMode : public Mode {

public:

    SleepMode();

    const char *getName() override;

    void enter() override;

    void tick() override;
};

#endif //NITELITE_SLEEPMODE_H
