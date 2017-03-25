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
#define EN1 5 //Speed control blue
#define IN1 2 //Direction green
#define IN2 3 //Direction yellow

//Motor B
#define EN2 6 //Speed control blue
#define IN3 7 //Direction green
#define IN4 8 //Direction yellow

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
//************************MOVEMENT***************************
void NanoDrive(int motor, int speed, int direction);
void NanoForward();
void NanoBackward();
void NanoStop();
void NanoTurn(int duration, char direction);
void _NanoOptocouplerLeft();
void _NanoOptocouplerRight();

extern char _Nano_left_direction;
extern char _Nano_right_direction;

extern int _Nano_left_ticks;
extern int _Nano_left_ticks_last;
extern bool _Nano_debug_print_encoder_left;

extern int _Nano_right_ticks;

extern long _Nano_left_micros;
extern long _Nano_left_micros_last;

extern float _Nano_left_speed;

void _NanoMotorTest();
void NanoDriveStraightForwardNaive(int distance);

#endif
