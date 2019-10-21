#ifndef NITELITE_RGBDISCOMODE_H
#define NITELITE_RGBDISCOMODE_H


#include "YourDiscoMode.h"

class RGBDiscoMode : public YourDiscoMode {
public:
    explicit RGBDiscoMode(Controller *controller);

    const char *getName() override;

protected:
    void chooseColor() override;
};


#endif //NITELITE_RGBDISCOMODE_H
