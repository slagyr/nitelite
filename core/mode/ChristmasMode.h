#ifndef NITELITE_CHRISTMASMODE_H
#define NITELITE_CHRISTMASMODE_H

#include "TravelingMode.h"

class ChristmasMode : public TravelingMode {

public:
    ChristmasMode(Controller *controller);

    const char *getName() override;

protected:
    void nextColor() override;

private:
    byte state;

};



#endif //NITELITE_CHRISTMASMODE_H
