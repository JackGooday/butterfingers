#include "Arduino.h"

int analogPin = A9;
int val = 0;

void setup(){
  Serial.begin(38400);
}

void loop(){
  val = analogRead(analogPin);
  Serial.println(val);
}
