/* This file is to include any functions for use 
during the autonomous routine. All functions and 
variables declared here will receive global scope.
All motors and objects used here will have brake modes
set according to AutonBrakeMode.h*/
#include "main.h"
#include "PID_Controller.h"
#include "Moving_Average_Filter.h"

void PIDSeconds(double seconds){
    /*
    This function follows a trapezoidal time-motion profile
    with a velocity-PID Control. Input the time of a single
    stage.
    */
    std::vector<double> plotterPass; //Creating empty vector for plotter.
    
    double rightAveraged = 0; //Empty values needed for output from PID Class
    double leftAveraged = 0;
    double resolvedCommandLeft = 0;
    double resolvedCommandRight = 0;

    bool doOnceFlag1 = true; //Flags used to reset integral term
    bool doOnceFlag2 = true;

    PIDController LeftPID(.78, 12.48, 0.0122); //Instances of PID Controller class. Tuned with Ziegler-Nichols
    PIDController RightPID(.78, 12.48, 0.0122);
    MovingAverageFilter LeftStream(3); //Instances of moving average filter class with box size of 3
    MovingAverageFilter RightStream(3);

    printf("%s \n", "{START}"); //Call out to the Plotter to receive data.
    pros::delay(1000);

    double powerPercent = 0.0; //Local variable for profile output.
    autonTimer.placeMark(); //Timer

    while (autonTimer.getDtFromMark().convert(second) <= 3.0 * seconds || leftDT.getActualVelocity() > 15.0){

        if (autonTimer.getDtFromMark().convert(second) <= (1.0 * seconds)){ //First stage of profile. Linear increase.
            powerPercent = autonTimer.getDtFromMark().convert(second) * (100.0/seconds);
        }

        else if (autonTimer.getDtFromMark().convert(second) <= 2.0 * seconds) //Second stage of profile. Constant.
        { 
            if (doOnceFlag1){ //Reset integral term at start of second stage
                LeftPID.resetIntegralTerm();
                RightPID.resetIntegralTerm();
                doOnceFlag1 = false;
            }
            powerPercent = 100.0;
        }

        else if (autonTimer.getDtFromMark().convert(second) <= 3.0 * seconds) //Third stage of profile. Linear decrease.
        {
            if (doOnceFlag2){ //Reset integral term at start of third stage.
                LeftPID.resetIntegralTerm();
                RightPID.resetIntegralTerm();
                doOnceFlag2 = false;
            } 
            powerPercent = 300.0 - (100.0/seconds) * autonTimer.getDtFromMark().convert(second);
        }

        leftAveraged = LeftStream.getFilteredVal(leftDT.getActualVelocity()); //Filter input.
        rightAveraged = RightStream.getFilteredVal(rightDT.getActualVelocity());
        resolvedCommandLeft = LeftPID.getResolvedCommand(200.0* (powerPercent/100.0), leftAveraged); //Resolve command with PID
        resolvedCommandRight = RightPID.getResolvedCommand(200.0 * (powerPercent/100.0), rightAveraged);

        if (resolvedCommandLeft < 0){ //Ensure robot doesn't start moving backwards because of residual P control.
            resolvedCommandLeft = 0;
        }
        if (resolvedCommandRight < 0){
            resolvedCommandRight = 0;
        }

        leftDT.moveVoltage(12000 * (resolvedCommandLeft/200.0)); //Send PID-adapted command to motors.
        rightDT.moveVoltage(12000 * (resolvedCommandRight/ 200.0));

        plotterPass = {autonTimer.getDtFromMark().convert(second), leftAveraged, rightAveraged, 2.0*powerPercent}; //Call out data to plotter.
        plotterPrint(plotterPass);

        pros::delay(20); //Might could go a bit faster?
    }

    leftDT.moveVelocity(0); //Just in case it isnt already.
    rightDT.moveVelocity(0);

    printf("%s \n", "{STOP}"); //Tell plotter to end data collection.
    pros::delay(1000);
}