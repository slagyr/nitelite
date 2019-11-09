#ifndef NITELITE_YOURBREATHMODE_H
#define NITELITE_YOURBREATHMODE_H


#include <Mode.h>

class YourBreathMode : public Mode {

public:

    YourBreathMode();

    const char *getName() override;

    void enter() override;

    void tick() override;

private:

    bool up;
    byte step;
};

#endif //NITELITE_YOURBREATHMODE_H
