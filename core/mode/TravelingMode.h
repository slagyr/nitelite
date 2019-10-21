#ifndef NITELITE_TRAVELINGMODE_H
#define NITELITE_TRAVELINGMODE_H


#include <Mode.h>

class TravelingMode : public Mode {

public:

    TravelingMode(Controller *controller);

    const char *getName() override;

    void enter() override;

    void tick() override;

protected:

    virtual void nextColor();
    Color *dest;

private:

    byte step;
    float rStep;
    float gStep;
    float bStep;
    bool traveling;

    void chooseDest();
};


#endif //NITELITE_TRAVELINGMODE_H
