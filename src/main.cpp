#include "Arduino.h"
#include <SBUS.h>
#include "Plotter.h"
#include <AccelStepper.h>

SBUS x8r(Serial1);
Plotter p;

uint16_t channels[16];
bool failSafe;
bool lostFrame;

//Create stepper objects. motor interface, stepPin, dirPin
// Motor interface = 1 (driver)
AccelStepper stepper1(1, 35, 34);
AccelStepper stepper2(1, 14, 13);
AccelStepper stepper3(1, 17, 16);

void setup(){
  
  x8r.begin();
  p.Begin();
  p.AddTimeGraph("5 variable time graph", 10000, "Channel 1 (A)", channels[0], "Channel 2 (E)", channels[1], "Channel 3 (T)", channels[2], "Channel 4 (R)", channels[3]);

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
  
  x8r.read(&channels[0], &failSafe, &lostFrame);
  p.Plot();

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
