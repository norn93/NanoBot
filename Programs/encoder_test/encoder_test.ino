#include "NanoBot.h"

void setup() {
  NanoInitialise();
  _NanoEncoderTest('l');
  delay(1000);
  _NanoEncoderTest('r');
}

void loop() {
}
