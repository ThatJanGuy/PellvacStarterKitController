#ifndef PellvacControllerBucket_h
#define PellvacControllerBucket_h
#include "Arduino.h"

class PellvacControllerBucket {
  public:
    PellvacControllerBucket();
    bool setup(int sensorPin, unsigned long neddedSensorUpTime);
    bool isFull();
    bool reset();
  private:
    int _pin;
    unsigned long _neededSensorUpTime;
    unsigned long _sensorTriggerMillis;
};

#endif