/*
 Robot.cpp - Library to control robots
 Created by D'Cruz A., Knowlden G., Siew K., November 2015
 Last updated 2015-11-03
 */
 
 //include header files
#include "NanoBot.h"
#include "PinChangeInt.h"

//variables
char _Nano_left_direction;
char _Nano_right_direction;

int _Nano_left_ticks;
int _Nano_left_ticks_last;
bool _Nano_debug_print_encoder_left;
long _Nano_debug_start_time_micros;

int _Nano_right_ticks;

long _Nano_left_micros;
long _Nano_left_micros_last;

float _Nano_left_speed;

//functions
void NanoInitialise() {
	//initialise the nanoBot
	
	//initialise the motors
	_NanoInitialiseMotors();
	
	//initialise the optocouplers
	pinMode(OPT_L, INPUT);
	PCintPort::attachInterrupt(OPT_L, _NanoOptocouplerLeft, RISING); //only detect slits (it's 0 on slit and 1 on wood so we are detecting moving from slit to wood right?)
	pinMode(OPT_R, INPUT);
	PCintPort::attachInterrupt(OPT_R, _NanoOptocouplerRight, RISING); //only detect slits
	
	
	//initialise the interrupts
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

void _NanoInitialiseMotors() {
	//initialise the motors according to the #defines from the header file
	pinMode(EN1, OUTPUT);
	pinMode(EN2, OUTPUT);
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
}

void NanoDrive(int motor, int speed, int direction)
{
  //Move specific motor at speed and direction
  //motor: 0 for B, 1 for A
  //speed: 0 is off, and 255 is full speed
  //direction: 1 is forward, 0 is backward

	boolean inPin1, inPin2;
  
	if (direction == -1) {
		//Backwards
		inPin1 = LOW;
		inPin2 = HIGH;
		_Nano_left_direction = 0;
		_Nano_right_direction = 0;
	} else if (direction == 1) {
		//Forward
		inPin1 = HIGH;
		inPin2 = LOW;
		_Nano_left_direction = 1;
		_Nano_right_direction = 1;
	} //else, we don't change the direction

	if (motor == 1) {
		digitalWrite(IN1, inPin1);
		digitalWrite(IN2, inPin2);
		analogWrite(EN1, speed);
	}
	if (motor == 0) {
		digitalWrite(IN3, inPin1);
		digitalWrite(IN4, inPin2);
		analogWrite(EN2, speed);
	}
}

//these next 2 functions will be replaced by ones with closed loops
void NanoForward(int duration) {
	NanoDrive(1, 255, 1);
	NanoDrive(0, 255, 1);
}

void NanoBackward(int duration) {
	NanoDrive(1, 255, -1);
	NanoDrive(0, 255, -1);
}

void NanoStop() {
	//stop moving
	NanoDrive(1, 0, 0);
	NanoDrive(0, 0, 0);
}

void NanoTurn(int duration, char direction) {
		if(direction == 'a'){
			NanoDrive(0, 255, 1);
		}
		else if(direction == 'd'){
			NanoDrive(1, 255, 1);
		}
}


void _NanoOptocouplerLeft() {
	//callback for the left optocoupler
	if (_Nano_left_direction) { //driving forward
		_Nano_left_ticks++;
	} else { //driving backward
		_Nano_left_ticks--;
	}
	
	if (_Nano_debug_print_encoder_left) {
		Serial.println(micros()-_Nano_debug_start_time_micros);
		//Serial.println(_Nano_left_ticks);
		//Serial.print("\t");
	}
	
}

void _NanoOptocouplerRight() {
	//callback for the right optocoupler
	if (_Nano_right_direction) { //driving forward
		_Nano_right_ticks++;
	} else { //driving backward
		_Nano_right_ticks--;
	}
}

void _NanoMotorTest() {
	//a small function to help tune the motor controllers
	
	Serial.println("Start speed test...");
	
	_Nano_debug_print_encoder_left = true;
	
	_Nano_debug_start_time_micros = micros();
	
	Serial.println(micros()-_Nano_debug_start_time_micros);
	//Serial.print("\t");
	//Serial.println(_Nano_left_ticks);
	
	NanoForward(500);
	
	/*for (int i = 0; i < 100; i++) {
		//Serial.println(_Nano_left_speed);
		Serial.println(_Nano_left_ticks);
		delay(5);
	}*/
	
	delay(1000);
	
	NanoStop();
	
	Serial.println("Switch off motor...");
	
	/*for (int i = 0; i < 100; i++) {
		//Serial.println(_Nano_left_speed);
		Serial.println(_Nano_left_ticks);
		delay(5);
	}*/
	
	delay(1000);
	
	_Nano_debug_print_encoder_left = false;
	
	Serial.println("Stop speed test.");
	
}

void NanoDriveStraightForwardNaive(int distance) {
	//still very much under development
	//this is a function to drive straight, and it is very cute and naive.
	//it doen't actually drive straight
	//it will drive a total distance of 'distance' mm
	
	//work out how many ticks we want to travel
	int distance_ticks = distance/(2*PI*RADIUS/SLITS);
	
	//get the initial positions. we will try and increase them by the same amount
	int final_left_ticks = _Nano_left_ticks + distance_ticks;
	int final_right_ticks = _Nano_right_ticks + distance_ticks;
	
	//the 'tick difference' should be maintained
	int initial_tick_difference = _Nano_left_ticks - _Nano_right_ticks;
	
	//initial power
	int left_power = 200;
	int right_power = 200;
	
	char to_rest = 5; //number of ticks it takes to stop. around 6 at 255 speed
	char thres = 1; //sensitivity to tick difference
	char inc = 3; //amount to increment or decrement the power
	char delay_time = 10; //ms to delay each loop
	
	while (_Nano_left_ticks + to_rest < final_left_ticks && _Nano_right_ticks + to_rest < final_right_ticks) {
		int tick_difference = _Nano_left_ticks - _Nano_right_ticks;
		int tick_delta = tick_difference - initial_tick_difference; //how far we have done left or right
		if (tick_difference > thres) {
			//we are too far to the right
			Serial.print(tick_difference);
			Serial.println(": To far to right");
			left_power -= inc;
			right_power += inc;
			Serial.print((int)left_power);
			Serial.println((int)right_power);
		} else if (tick_difference < -thres) {
			//we are too far to the left
			Serial.print(tick_difference);
			Serial.println(": To far to left");
			left_power += inc;
			right_power -= inc;
			Serial.print((int)left_power);
			Serial.println((int)right_power);
		} else {
			Serial.print(tick_difference);
			Serial.println(": Good");
			Serial.print((int)left_power);
			Serial.println((int)right_power);
		}
		
		//bound them
		if (left_power > 255) {
			left_power = 255;
		}
		if (left_power < 0) {
			left_power = 0;
		}
		if (right_power > 255) {
			right_power = 255;
		}
		if (right_power < 0) {
			right_power = 0;
		}
		
		//begin driving, leave room for corrections
		NanoDrive(1, left_power, 1);
		NanoDrive(0, right_power, 1);
		
		delay(delay_time); //give enough time for a tick or two
	}
	
	//we will arrive if we slow down now
	NanoDrive(1, 0, 1);
	NanoDrive(0, 0, 1);
}

//ISR(TIMER1_COMPA_vect) {
//	/*long time_micros = micros();
//	
//	if (time_micros - _Nano_left_micros_last > 50000) { //if nothing for 50ms
//		//_Nano_left_speed = 0;
//	}*/
//	
//	//calculate wheel speed
//	/*
//	_Nano_left_micros = micros();
//	
//	_Nano_left_speed = 1000000*(2*PI/SLITS)/(_Nano_left_micros - _Nano_left_micros_last); //speed in radians/second
//	
//	_Nano_left_micros_last = _Nano_left_micros;*/
//	
//	//really calculate speed
//	
//	//code for PID control
//	
//	/*float Kp = 0.8;
//	float Ki = 0;
//	float Kd = 0;
//
//	static int r_old=0, e_old=0, e_old2=0;	
//	e_func = v_des - _Nano_left_speed;
//	r_mot = r_old + Kp*(e_func-e_old) + Ki*(e_func+e_old)/2 + Kd*(e_func - 2* e_old + e_old2);
//	r_mot = min(r_mot, +100); // limit output 
//	r_mot = max(r_mot, -100); // limit output 
//	e_old2 = e_old;
//	e_old = e_func;
//	r_old = r_mot;*/
//}

