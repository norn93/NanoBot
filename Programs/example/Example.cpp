#include "Example.h"

Robot::Robot() { //constructor
	pinMode(BUTTON_PIN, INPUT);
}

void Robot::_buttonPress() {
	Serial.println("Woo!");
}