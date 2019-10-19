#ifndef NITELITE_RGBFADEMODE_H
#define NITELITE_RGBFADEMODE_H


#include <Mode.h>

class RGBFadeMode : public Mode {

public:

    RGBFadeMode(Controller *controller);

    const char *getName() override;

    void enter() override;

    void tick() override;

private:

    byte state;
};


#endif //NITELITE_RGBFADEMODE_H
