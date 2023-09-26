#include "Arduino.h"
#include "PellvacControllerBucket.h"

PellvacControllerBucket::PellvacControllerBucket(){
  //Empty constructor for better instantiation control.
}

bool PellvacControllerBucket::setup(int sensorPin, unsigned long neededSensorUpTime){
  //Setting the private variables and setting up the sensorPin
  _pin = sensorPin;
  Serial.print("Sensor pin is set to ");
  Serial.print(_pin, DEC);
  Serial.println(".");

  _neededSensorUpTime = neededSensorUpTime;
  Serial.print("The minimum time of a stable signal is set to ");
  Serial.print(_neededSensorUpTime, DEC);
  Serial.println(".");

  _sensorTriggerMillis = 0UL;

  pinMode(_pin, INPUT);
  Serial.println("Bucket pin set to INPUT mode.");
  Serial.println("Setting/resetting bucket done.");
  
  return true;
}

bool PellvacControllerBucket::isFull(){
  if (digitalRead(_pin) == LOW && _sensorTriggerMillis == 0){
    return false;
  }

  if (digitalRead(_pin) == HIGH && _sensorTriggerMillis == 0){
    _sensorTriggerMillis = millis();
    Serial.println("Bucket sensor switched to HIGH.");

    return false;
  }

  if (digitalRead(_pin) == LOW && _sensorTriggerMillis > 0){
    _sensorTriggerMillis = 0;
    Serial.println("Bucket sensor switched to LOW.");

    return false;
  }

  if (digitalRead(_pin) == HIGH && _sensorTriggerMillis + _neededSensorUpTime > millis()){
    return false;
  }

  Serial.println("Bucket is full.");
  return true;
}

bool PellvacControllerBucket::reset(){
  Serial.println("Resetting bucket.");

  setup(_pin, _neededSensorUpTime);
  
  return false;
}