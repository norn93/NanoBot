#include "NanoBot.h"

void setup() {
  // put your setup code here, to run once:
  NanoInitialise();
  _NanoInitialiseMotors();
  NanoForward(500);
  NanoStop();
}

void loop() {

}
