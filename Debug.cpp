/*
 Debug.cpp - Library to debug robots
 Created by D'Cruz A., Knowlden G., Siew K., November 2015
 Last updated 2015-11-03
 */
 
 //include header files
#include "Debug.h"
#include "PinChangeInt.h"

//variables

//functions

/*
 *Prints out encoder outputs to ensure they are working
 *@mode: 1 for digital output, 0 for analog output
 */ 
void debugEncoder(int mode){

	delay(500);
	int statusOptR = 0;
	int statusOptL = 0;

	if (mode==1)
	{
		statusOptR = digitalRead(OPT_R);
		statusOptL = digitalRead(OPT_L);
	}
	else 
	{
		statusOptR = analogRead(OPT_R);
		statusOptL = analogRead(OPT_L);	
	}	

	Serial.println("Right " + String(statusOptR));
	Serial.println("Left "  + String(statusOptL));
}