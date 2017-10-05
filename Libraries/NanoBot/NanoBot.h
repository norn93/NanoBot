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
#define EN1 6 //PWM speed control
#define IN1 2 //Direction control 1
#define IN2 3 //Direction control 2

//Motor B
#define EN2 7 //PWM speed control
#define IN3 4 //Direction control 1
#define IN4 5 //Direction control 2

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
void NanoDrive(float motor_a_speed, float motor_b_speed);
void NanoForward(int duration);
void NanoBackward(int duration);
void NanoStop();
void NanoTurn(int duration, char turn_direction);
void _NanoOptocouplerLeft();
void _NanoOptocouplerRight();

extern char _Nano_left_direction; //the current direction of the left motor
extern char _Nano_right_direction; //the current direction of the right motor

extern int _Nano_left_ticks; //keeps track of current position of the left encoder
extern int _Nano_right_ticks; //keeps track of current position of the right encoder

extern bool _Nano_debug_print_encoder_left; //controls if the left encoder is printed
extern bool _Nano_debug_print_encoder_right; //controls if the right encoder is printed

extern int _Nano_left_ticks_last;
extern int _Nano_right_ticks_last;

extern long _Nano_left_micros;
extern long _Nano_left_micros_last;

extern long _Nano_right_micros;
extern long _Nano_right_micros_last;

extern float _Nano_left_speed;
extern float _Nano_right_speed;

//void _NanoEncoderTest(char encoder_side);
void NanoDriveStraightForwardNaive(int distance);

#endif
