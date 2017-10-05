#include "ANDRIS.h"
#include "PinChangeInt.h"

Robot myRobot;

void setup() {
  //PCintPort::attachInterrupt(OPT_L,  optocouplerLeft, RISING);
  Serial.begin(9600);
  Serial.println("Hello, World!");

  //myRobot.drive(1, 1);
  //delay(1000);
  //myRobot.drive(-1, -1);
}

void optocouplerLeft() {
  myRobot._optocouplerLeft();
}

void loop() {
  //Serial.println((int)myRobot._left_ticks);
  //delay(1000);
}
