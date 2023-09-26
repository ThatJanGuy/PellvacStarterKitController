#include "Arduino.h"
#include "PellvacControllerScrew.h"

PellvacControllerScrew::PellvacControllerScrew(){
  //Empty constructor for better instantiation control.
  Serial.println("PellvacControllerScrew object instantiated.");
}

bool PellvacControllerScrew::setup(int screwPin){
  //Setting the private variables and setting up the sensorPin
  _pin = screwPin;
  Serial.print("Screw pin is set to ");
  Serial.print(_pin, DEC);
  Serial.println(".");

  pinMode(_pin, OUTPUT);
  Serial.println("Screw pin set to OUTPUT mode.");
  
  stop();
  return true;
}

bool PellvacControllerScrew::start(){
  digitalWrite(_pin, HIGH);
  Serial.println("Screw start signal sent.");
  
  return true;
}

bool PellvacControllerScrew::stop(){
  digitalWrite(_pin, LOW);
  Serial.println("Screw stop signal sent.");

  return true;
}