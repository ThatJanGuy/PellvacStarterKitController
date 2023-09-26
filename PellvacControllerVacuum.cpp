#include "Arduino.h"
#include "PellvacControllerVacuum.h"

PellvacControllerVacuum::PellvacControllerVacuum(){
  //Empty constructor for better instantiation control.
  Serial.println("PellvacControllerVacuum object instantiated.");
}

bool PellvacControllerVacuum::setup(int vacuumPin){
  //Setting the private variables and setting up the sensorPin
  _pin = vacuumPin;
  Serial.print("Vacuum pin is set to ");
  Serial.print(_pin, DEC);
  Serial.println(".");

  pinMode(_pin, OUTPUT);
  Serial.println("Vacuum pin set to OUTPUT mode.");
  
  stop();
  return true;
}

bool PellvacControllerVacuum::start(){
  digitalWrite(_pin, HIGH);
  Serial.println("Vacuum start signal sent.");

  return true;
}

bool PellvacControllerVacuum::stop(){
  digitalWrite(_pin, LOW);
  Serial.println("Vacuum stop signal sent.");
  
  return true;
}