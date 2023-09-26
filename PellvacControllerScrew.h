#ifndef PellvacControllerScrew_h
#define PellvacControllerScrew_h
#include "Arduino.h"

class PellvacControllerScrew {
  public:
    PellvacControllerScrew();
    bool setup(int screwPin);
    bool start();
    bool stop();
  private:
    int _pin;

};

#endif