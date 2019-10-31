#ifndef NITELITE_HALLOWEENMODE_H
#define NITELITE_HALLOWEENMODE_H

#include "TravelingMode.h"

class HalloweenMode : public TravelingMode {

public:

    HalloweenMode(Controller *controller);

    const char *getName() override;

    void tick() override;

protected:
    void nextColor() override;

private:

    byte state;
    bool lightning;
};

#endif //NITELITE_HALLOWEENMODE_H
