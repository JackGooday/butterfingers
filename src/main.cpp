#include "Arduino.h"
#include <SBUS.h>
#include "Plotter.h"

SBUS x8r(Serial1);
Plotter p;

uint16_t channels[16];
bool failSafe;
bool lostFrame;

void setup() {
  x8r.begin();
  p.Begin();
  p.AddTimeGraph("5 variable time graph", 10000, "Channel 1 (A)", channels[0], "Channel 2 (E)", channels[1], "Channel 3 (T)", channels[2], "Channel 4 (R)", channels[3]);
}

void loop() {
  x8r.read(&channels[0], &failSafe, &lostFrame);
  p.Plot();
}
