#ifndef NITELITE_YOURDISCOMODE_H
#define NITELITE_YOURDISCOMODE_H


#include <Mode.h>

class YourDiscoMode : public Mode {

public:

    YourDiscoMode(Controller *controller);

    const char *getName() override;

    void enter() override;

    void tick() override;

protected:

    byte beatCount;
    bool repeat;
    byte beat;
    byte beat1;
    byte beat2;
    Color *color;

    virtual void chooseColor();
    virtual void writeColor();

    void pass();

    void quarters();

    void eigths();

    void stayingAlive();

    void dancingQueen();

    void youAreTheDancingQueen();

    void anotherOneBytesTheDust();

    void YMCA();

    void chooseBeats();
};


#endif //NITELITE_YOURDISCOMODE_H
