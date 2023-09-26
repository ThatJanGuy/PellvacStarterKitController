#include "PellvacControllerBucket.h"
#include "PellvacControllerScrew.h"
#include "PellvacControllerVacuum.h"

// Assign the pins
#define VacuumPin 6
#define ScrewPin 11
#define BucketPin 3

// Set different variables
#define RequiredBucketSensorStableTime 1000UL
#define ScrewStartDelay 2000UL
#define MaxVacuumOnTime 300000UL // 5 minutes
#define BucketEmptyingTime 12000UL
#define SerialSpeed 31250

PellvacControllerBucket Bucket;
PellvacControllerScrew Screw;
PellvacControllerVacuum Vacuum;

void setup() {
  Serial.begin(SerialSpeed);
  while (!Serial) {};
  Serial.print("Serial communication started with a baud rate of ");
  Serial.print(SerialSpeed, DEC);
  Serial.println(".");

  Serial.println("####################################");
  Serial.println("Starting setup.");
  Serial.println();

  // Setup the objects by passing pins and other variables.
  Serial.println("Setting up the bucket.");
  Bucket.setup(BucketPin, RequiredBucketSensorStableTime);
  Serial.println();

  Serial.println("Setting up the screw.");
  Screw.setup(ScrewPin);
  Serial.println();

  Serial.println("Setting up the vacuum.");
  Vacuum.setup(VacuumPin);
  Serial.println();

  Serial.println("Setup done. Entering loop.");
  Serial.println("####################################");
  Serial.println();
}


void loop() {
  // Declare counters for cycles and errors.
  // "static" means that they don't get set to the initial value 
  // every time the code gets here.
  static int cycles = 1;
  static int errors = 0;
  Serial.print("Entering cycle ");
  Serial.print(cycles, DEC);
  Serial.println(".");

  // Start up the machinery.
  Vacuum.start();
  delay(ScrewStartDelay);
  Screw.start();

  // Stay in this loop until the bucket is full.
  // If the loop stays on for too long, the bucket's air seal might not have engaged.
  // By setting a max time for the vacuum to run before we cut it, we avoid that
  // the test setup get stuck with a turned on vacuum. Failing the maximum time 
  // is considered an error.
  unsigned long vacuumPowerOnTime = millis();
  Serial.println("Starting Bucket monitoring.");
  while (Bucket.isFull() == false){
    if (vacuumPowerOnTime + MaxVacuumOnTime < millis()){
      Serial.println("ERROR: MaxVacuumOnTime expired.");
      errors++;
      break;
    }
  }

  Vacuum.stop();
  Screw.stop();
  Serial.print("Giving bucket ");
  Serial.print(BucketEmptyingTime, DEC);
  Serial.println("ms to empty.");
  delay(BucketEmptyingTime);
  Serial.println("BucketEmptyingTime passed.");

  Bucket.reset();

  Serial.println("####################################");
  Serial.print("Cycle ");
  Serial.print(cycles, DEC);
  Serial.println(" finished.");
  Serial.print("Errors encountered: ");
  Serial.print(errors, DEC);
  Serial.println(".");
  Serial.println("####################################");
  Serial.println();

  cycles++;
}