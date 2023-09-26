#ifndef PellvacControllerVacuum_h
#define PellvacControllerVacuum_h
#include "Arduino.h"

class PellvacControllerVacuum {
  public:
    PellvacControllerVacuum();
    bool setup(int VacuumPin);
    bool start();
    bool stop();
  private:
    int _pin;

};

#endif