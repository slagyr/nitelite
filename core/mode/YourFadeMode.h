#ifndef NITELITE_YOURFADEMODE_H
#define NITELITE_YOURFADEMODE_H


#include <Mode.h>

class YourFadeMode : public Mode {

public:

    YourFadeMode(Controller *controller);

    const char *getName() override;

    void enter() override;

    void tick() override;

private:

    bool up;
    byte step;
};

#endif //NITELITE_YOURFADEMODE_H
