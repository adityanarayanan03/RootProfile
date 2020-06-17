#include "main.h"
#include "motor.h"			//Included here to give motor declarations global scope.
#include "sensor.h"			//Sensor declarations use motors.
#include "globalFunctions.h" //Functions for both auton and OPControl
#include "opfunctions.h"	//User control functions
#include "AutonFunctions.h" //Included here to avoid function-in-function declarations.

void initialize() { pros::lcd::initialize(); }

void disabled() {}

void competition_initialize() {}

void autonomous()
{
//To edit brake modes, edit only th .h files. Do not edit straightaway here.
	#include "AutonBrakeMode.h"
	PIDSeconds(.5);
}

void opcontrol()
{
	Controller controller;
	//To edit brake modes, edit in the .h files. Do not edit straightaway here.
	#include "UserBrakeMode.h"
	printf("%s \n", "{STOP}");
	pros::delay(1000);
}
