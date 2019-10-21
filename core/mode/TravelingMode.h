#ifndef NITELITE_TRAVELINGMODE_H
#define NITELITE_TRAVELINGMODE_H


#include <Mode.h>

class TravelingMode : public Mode {

public:

    TravelingMode(Controller *controller);

    const char *getName() override;

    void enter() override;

    void tick() override;

private:

    Color *dest;
    byte step;
    float rStep;
    float gStep;
    float bStep;
    bool traveling;

    void chooseDest();

    void nextColor();
};


#endif //NITELITE_TRAVELINGMODE_H
