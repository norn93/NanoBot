#include "NanoBot.h"

void setup() {
  NanoInitialise();
  //Serial.println("I'm alive");
}

void serialEvent() {
  //gets the serial input from the BT module
  //does this once per loop automatically
  //(read arduino docs for serialEvent() )
  while (Serial.available()) {
    char inCommand =  (char)Serial.read();
    if (inCommand == 'w') {
      NanoForward(500);
    }
    if (inCommand == 's') {
      NanoBackward(500);
    }
    if (inCommand == 'a') {
      NanoTurn('l', 150);
    }
    if (inCommand == 'd') {
      NanoTurn('r', 150);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
