/* This file is to include any functions for use 
during the autonomous routine. All functions and 
variables declared here will receive global scope.
All motors and objects used here will have brake modes
set according to AutonBrakeMode.h*/
#include "main.h"


int setVoltageByPercent(int percent){
    /*
    This function is intended to take a percentage for speed and return
    a scaled value for setting voltage.
    */
    return (percent/100.0)*12000;
}

void forward(){
    autonTimer.placeMark();

    std::vector<double> plotterPass;

    printf("%s \n", "{START}");
    pros::delay(1000);

    while(autonTimer.getDtFromMark().convert(second) < 10.0){
        plotterPass = {autonTimer.getDtFromMark().convert(second), 2.0, 5.0};
        plotterPrint(plotterPass);
        pros::delay(20);
    }

    printf("%s \n", "{STOP}");
    pros::delay(1000);
}