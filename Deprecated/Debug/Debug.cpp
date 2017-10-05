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
void debugEncoders(int mode){

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

void debugMotorSpeed() {
	//turn the left motor on at some speed < 255
	NanoDrive(0.6, 0);
	
	for(int i = 0; i < 20; i++) {
		delay(100);
		Serial.print(_Nano_left_ticks);
	}
	
	NanoStop();
	
	for(int i = 0; i < 20; i++) {
		delay(100);
		Serial.print(_Nano_left_ticks);
	}
}

void debugMotorEncoder(char encoder_side) {
  //a small function to help test the encoders

  //encoder_side: 'l' or 'r' encoder to be tested

  if (encoder_side == 'r') {
    Serial.println("Start right encoder test...");
    _Nano_debug_print_encoder_right = true;
  } else if (encoder_side == 'l') {
    Serial.println("Start left encoder test...");
    _Nano_debug_print_encoder_left = true;
  } else {
    Serial.println("ERROR: Invalid encoder type.");
    return;
  }

  _Nano_debug_start_time_micros = micros();

  Serial.println(micros() - _Nano_debug_start_time_micros);

  if (encoder_side == 'r') {
    NanoDrive(0, 1);
  } else {
    NanoDrive(1, 0);
  }
  delay(1000);
  NanoDrive(0, 0);
  Serial.println("Switch off motor...");
  delay(1000);

  if (encoder_side == 'r') {
    Serial.println("Stop right encoder test.");
    _Nano_debug_print_encoder_right = false;
  } else if (encoder_side == 'l') {
    Serial.println("Stop left encoder test.");
    _Nano_debug_print_encoder_left = false;
  }
}