#include <SoftwareSerial.h>
//#include "NanoBot.h"

SoftwareSerial mySerial(8, 9); // RX, TX

void setup() {
  // put your setup code here, to run once:
  //NanoInitialise();
  //_NanoInitialiseMotors();
  mySerial.begin(9600);
  mySerial.println("Hello, World!");
}

void loop() {



}


