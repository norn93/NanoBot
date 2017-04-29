#include "NanoBot.h"

void setup() {
  // put your setup code here, to run once:
  NanoInitialise();
  _NanoInitialiseMotors();
  Serial.begin(9600);
   _NanoMotorTest(); 
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
      delay(500);
      NanoStop();
    }
    if (inCommand == 's') {
      NanoBackward(500);
      delay(500);
      NanoStop();
    }
    if (inCommand == 'a') {
      NanoTurn(500, inCommand);
      delay(500);
      NanoStop();
    }
    if (inCommand == 'd') {
      NanoTurn(500, inCommand);
      delay(500);
      NanoStop();
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
