#include "Arduino.h"
#include <SBUS.h>
#include "Plotter.h"
#include <AccelStepper.h>

Plotter p;

SBUS rsxr(Serial1);
uint16_t channels[16];
bool failSafe;
bool lostFrame;

//Create stepper objects. motor interface, stepPin, dirPin
// Motor interface = 1 (driver)
AccelStepper stepper1(1, 35, 34);
AccelStepper stepper2(1, 14, 13);
AccelStepper stepper3(1, 17, 16);

void setup(){

  p.Begin();
  p.AddTimeGraph("5 variable time graph", 10000, "Channel 1 (A)", channels[0], "Channel 2 (E)", channels[1], "Channel 3 (T)", channels[2], "Channel 4 (R)", channels[3]);

  rsxr.begin();

  // Set max speeds (steps per second) and accelerations
  stepper1.setMaxSpeed(4000);
  stepper2.setMaxSpeed(1000);
  stepper3.setMaxSpeed(1000);
  stepper1.setAcceleration(400);
  stepper2.setAcceleration(400);
  stepper3.setAcceleration(400);

  // Switch on motors
  pinMode(36, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(18, OUTPUT);
  digitalWrite(36, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(18, HIGH);

}

void loop(){

  rsxr.read(&channels[0], &failSafe, &lostFrame);
  p.Plot();

  //if(stepper1.distanceToGo() == 0){
  //  digitalWrite(36, LOW);
  //}
  //if(stepper2.distanceToGo() == 0){
  //  digitalWrite(15, LOW);
  //}
  //if(stepper3.distanceToGo() == 0){
  //  digitalWrite(18, LOW);
  //}

  stepper1.moveTo(channels[0]);
  stepper2.moveTo(channels[1]);
  stepper3.moveTo(channels[2]);

  stepper1.run();
  stepper2.run();
  stepper3.run();

}
