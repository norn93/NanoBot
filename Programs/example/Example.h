#ifndef Example_h
#define Example_h

#include "Arduino.h"

#define BUTTON_PIN A0 //the pin I want to listen to

class Robot {
	public:
		Robot(); //constructor
		
		PCICR = 0x02; //enable PCINT1 interrupt for analog pins A0 - A7
		PCMSK1 = 0b00000001; //mask for A0 only
		
	private:
		void _buttonPress(); //this function should be called by the ISR (Interrupt Service Routine) when a button is pressed
};

ISR(PCINT1_vect) { //This low level function gets called when pins on PCINT1_vect change state, after the mask has ben applied. So, in this case, it will only trigger 
  if (digitalRead(BUTTON_PIN) == 0) {
    /* Here is the bit where we should call the Robot._buttonPress() event. */
  }
}

#endif