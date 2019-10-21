#ifndef NITELITE_JULY4THMODE_H
#define NITELITE_JULY4THMODE_H


#include "FireworksMode.h"

class July4thMode : public FireworksMode {

public:
    July4thMode(Controller *controller);

    const char *getName() override;

protected:
    void chooseColor() override;
};


#endif //NITELITE_JULY4THMODE_H
