#ifndef NITELITE_YOURBEATMODE_H
#define NITELITE_YOURBEATMODE_H

#include <Mode.h>

class YourBeatMode : public Mode {

public:

    YourBeatMode(Controller *controller);

    const char *getName() override;

    void enter() override;

    void tick() override;

private:

    bool up;
    float multiplier;
};


#endif //NITELITE_YOURBEATMODE_H
