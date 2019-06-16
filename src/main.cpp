
#include "Arduino.h"

#include <SBUS.h>

// a SBUS object, which is on hardware
// serial port 1
SBUS x8r(Serial1);

// channel, fail safe, and lost frames data
uint16_t channels[16];
bool failSafe;
bool lostFrame;

void setup() {
  // begin the SBUS communication
  x8r.begin();
  Serial.begin(9600);
}

void loop() {

  // look for a good SBUS packet from the receiver
  if(x8r.read(&channels[0], &failSafe, &lostFrame)){

    // write the SBUS packet to an SBUS compatible servo
    //x8r.write(&channels[0]);
    Serial.println("Good packet");
  }
}
