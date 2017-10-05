/*
 Debug.h - Library to debug robots
 Created by D'Cruz A., Knowlden G., Siew K., November 2015
 Last updated 2015-11-03
 */
 
 // ensure this library description is only included once
#ifndef Debug_h
#define Debug_h

// include necessary libraries
#include "Arduino.h"
#include "Debug.h"

void debugEncoders(int mode);
void debugMotorSpeed();
void debugMotorEncoder(char encoder_side);

#endif