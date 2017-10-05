/*
 ANDRIS.cpp - Library to control ANDRIS
 Created by Knowlden G., October 2017
 Heavily inspired by Robot.h - Library to control robots, created by D'Cruz A., Knowlden G., Siew K., November 2015
 Last updated 2017-10-05
*/

//include header files
#include "ANDRIS.h"
//#include "PinChangeInt.h"

Robot::Robot() { //constructor
	//initialise ANDRIS
	_initialiseMotors();
	
	//initialise the optocouplers
	_initialiseOptocouplers();
	
	//initialise the interrupts
	_initialiseTimerInterupts();
}

Robot::~Robot() { //deconstructor
	
}

void Robot::_initialiseMotors() {
	//initialise the motors according to the #defines from the header file
	pinMode(EN1, OUTPUT);
	pinMode(EN2, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
}

void Robot::_initialiseOptocouplers() {
	pinMode(OPT_L, INPUT);
	pinMode(OPT_R, INPUT);
	
	//PCICR = 0x02; //enable PCINT1 interrupt for analog pins
	//PCMSK1 = 0b00000011; //mask for A0 and A1 and A2
	
	//enableInterrupt(OPT_L, _optocouplerLeft, RISING); //only detect slits (it's 0 on slit and 1 on wood so we are detecting moving from slit to wood right?)
	//enableInterrupt(OPT_R, _optocouplerRight, RISING); //only detect slits
}

void Robot::_optocouplerLeft() {
  //callback for the left optocoupler
  if (_left_direction) { //driving forward
    _left_ticks++;
  } else { //driving backward
    _left_ticks--;
  }

  if (_debug_print_encoder_left) {
    Serial.println(micros() - _debug_start_time_micros);
    //Serial.println(_Nano_left_ticks);
    //Serial.print("\t");
  }

}

void Robot::_optocouplerRight() {
  //callback for the right optocoupler
  if (_right_direction) { //driving forward
    _right_ticks++;
  } else { //driving backward
    _right_ticks--;
  }

  if (_debug_print_encoder_right) {
    Serial.println(micros() - _debug_start_time_micros);
    //Serial.println(_Nano_left_ticks);
    //Serial.print("\t");
  }
}

void Robot::_initialiseTimerInterupts() {
	cli(); //pause interrupts to set up sensitive stuff

	//set timer1 interrupt at 10Hz
	TCCR1A = 0;// set entire TCCR1A register to 0
	TCCR1B = 0;// same for TCCR1B
	TCNT1  = 0;//initialize counter value to 0
	// set compare match register for 100hz increments
	OCR1A = 155;// = (16*10^6) / (100*1024) - 1 (must be <65536)
	// turn on CTC mode
	TCCR1B |= (1 << WGM12);
	// Set CS10 and CS12 bits for 1024 prescaler
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);

	sei(); //resume interrupts
}

void Robot::drive(float motor_a_speed, float motor_b_speed) {
	//Move both motors at defined speeds/directions
	//speed is truncated in the range {-1 <= speed <= 1}
	//positive speeds are forward, negative speeds are backward

	//truncate speeds
	if (motor_a_speed > 1) {
		motor_a_speed = 1;
	} else if (motor_a_speed < -1) {
		motor_a_speed = -1;
	}
	if (motor_b_speed > 1) {
		motor_b_speed = 1;
	} else if (motor_b_speed < -1) {
		motor_b_speed = -1;
	}

	boolean in1, in2, in3, in4;

	if (motor_a_speed > 0) { //forward
		in1 = LOW;
		in2 = HIGH;
		_left_direction = 1; //forward
	} else if (motor_a_speed < 0) { //backward
		in1 = HIGH;
		in2 = LOW;
		_left_direction = 0; //backward
	} else { //stop
		in1 = LOW;
		in2 = LOW;
	}

	if (motor_b_speed > 0) { //forward
		in3 = LOW;
		in4 = HIGH;
		_right_direction = 1; //forward
	} else if (motor_b_speed < 0) { //backward
		in3 = HIGH;
		in4 = LOW;
		_right_direction = 0; //backward
	} else { //stop
		in3 = LOW;
		in4 = LOW;
	}

	//set the motor directions
	digitalWrite(IN1, in1);
	digitalWrite(IN2, in2);
	digitalWrite(IN3, in3);
	digitalWrite(IN4, in4);

	//run the motors at the required speeds
	int speed_a = abs(motor_a_speed) * 255;
	int speed_b = abs(motor_b_speed) * 255;
	analogWrite(EN1, speed_a);
	analogWrite(EN2, speed_b);
}
