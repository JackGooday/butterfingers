
/*
The two geared motors run pretty smooth set to 1/32 step @ 1000 steps/sec
For the non-geared motor, full step @ 1000 steps/sec (why???)
*/

#include "Arduino.h"
#include <AccelStepper.h>

//Create stepper objects. motor interface, stepPin, dirPin
// Motor interface = 1 (driver)
AccelStepper stepper1(1, 3, 2);
AccelStepper stepper2(1, 6, 5);
AccelStepper stepper3(1, 9, 8);

void setup(){

  // Set max speeds (steps per second)
  stepper1.setMaxSpeed(1000);
  stepper2.setMaxSpeed(1000);
  stepper3.setMaxSpeed(1000);

  // Switch on motors
  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(10, HIGH);

  // Set speeds of motors
  stepper1.setSpeed(1000);
  stepper2.setSpeed(1000);
  stepper3.setSpeed(1000);

}

void loop(){
  stepper1.runSpeed();
  stepper2.runSpeed();
  stepper3.runSpeed();
}
