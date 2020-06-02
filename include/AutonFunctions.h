/* This file is to include any functions for use 
during the autonomous routine. All functions and 
variables declared here will receive global scope.
All motors and objects used here will have brake modes
set according to AutonBrakeMode.h*/
#include "main.h"
//void forward(float targetDistance, int maxSpeed = 170);

int setVoltageByPercent(int percent){
    /*
    This function is intended to take a percentage for speed and return
    a scaled value for setting voltage.
    */
    return (percent/100.0)*12000;
}

void forward(){
    autonTimer.placeMark();

    std::vector<float> plotterPass;

    printf("%s \n", "{START}");
    pros::delay(1000);

    while(autonTimer.getDtFromMark().convert(second) < 10.0){
        plotterPass = {1.0,2.0,3.0,4.0,5.0};
        plotterPrint(plotterPass);
    }

    printf("%s \n", "{STOP}");
    pros::delay(1000);
}