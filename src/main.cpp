
/*
The two geared motors run pretty smooth set to 1/32 step @ 1000 steps/sec
For the non-geared motor, full step @ 1000 steps/sec (why???)
*/

#include "Arduino.h"
#include <AccelStepper.h>

//Create stepper objects. motor interface, stepPin, dirPin
// Motor interface = 1 (driver)
AccelStepper stepper1(1, 35, 34);
AccelStepper stepper2(1, 14, 13);
AccelStepper stepper3(1, 17, 16);

void setup(){

  // Set max speeds (steps per second) and accelerations
  stepper1.setMaxSpeed(4000);
  stepper2.setMaxSpeed(1000);
  stepper3.setMaxSpeed(1000);
  stepper1.setAcceleration(200);
  stepper2.setAcceleration(50);
  stepper3.setAcceleration(50);

  // Set positions to move to
  stepper1.moveTo(10000);
  stepper2.moveTo(10000);
  stepper3.moveTo(10000);

  // Switch on motors
  pinMode(36, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(18, OUTPUT);
  digitalWrite(36, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(18, HIGH);

}

void loop(){

  if(stepper1.distanceToGo() == 0){
    digitalWrite(36, LOW);
  }
  if(stepper2.distanceToGo() == 0){
    digitalWrite(15, LOW);
  }
  if(stepper3.distanceToGo() == 0){
    digitalWrite(18, LOW);
  }

  stepper1.run();
  stepper2.run();
  stepper3.run();

}
