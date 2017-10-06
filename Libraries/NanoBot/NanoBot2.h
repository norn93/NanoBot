/*
 Robot.h - Library to control robots
 Created by D'Cruz A., Knowlden G., Siew K., November 2015
 Last updated 2015-11-03
 */
 
// ensure this library description is only included once
#ifndef NanoBot_h
#define NanoBot_h

// include necessary libraries
#include "Arduino.h"

//Motor A
#define EN1 6 //Speed control blue
#define IN1 2 //Direction green
#define IN2 3 //Direction yellow

//Motor B
#define EN2 7 //Speed control blue
#define IN3 4 //Direction green
#define IN4 5 //Direction yellow

//encoders
#define OPT_L A0
#define OPT_R A1

//constants
#define SLITS 20
#define RADIUS 33

//************************FUNCTIONS***************************
//************************INITIALISATION***************************
void NanoInitialise();
void _NanoInitialiseMotors();
void _NanoInitialiseOptocouplers();
void _NanoInitialiseTimerInterrupts();
//************************MOVEMENT***************************
void NanoDrive(float motor_a_speed, float motor_b_speed);
void NanoForward(float speed, int duration);
void NanoBackward(float speed, int duration);
void NanoStop();
void NanoTurn(float speed, int duration, char turn_direction);
void _NanoOptocouplerLeft();
void _NanoOptocouplerRight();

extern char _Nano_left_direction;
extern char _Nano_right_direction;

extern int _Nano_left_ticks;
extern int _Nano_right_ticks;

extern bool _Nano_debug_print_encoder_left;
extern bool _Nano_debug_print_encoder_right;

extern long _Nano_left_micros; //for the PID stuff later
extern long _Nano_left_micros_last; //for the PID stuff later
extern float _Nano_left_speed; //for the PID stuff later

//************************TESTING/DEBUGGING***************************
void _NanoMotorTest();
void _NanoEncoderTest(char encoder_side);

//void NanoDriveStraightForwardNaive(int distance); //DEPRECATED

#endif
