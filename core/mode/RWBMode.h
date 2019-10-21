#ifndef NITELITE_RWBMODE_H
#define NITELITE_RWBMODE_H


#include "TravelingMode.h"

class RWBMode : public TravelingMode {

public:
    RWBMode(Controller *controller);

    const char *getName() override;

protected:
    void nextColor() override;

private:
    byte state;

};


#endif //NITELITE_RWBMODE_H
