#include "main.h"

class PIDController
/*
Class for our standard PID Controller.
Aint nobody got time to figure out how to use the Okapi one.
*/
{
public:
    double kP; //Variables for constants.
    double kI;
    double kD;
    double pGain = 0.0; //Variables for gains.
    double iGain = 0.0;
    double dGain = 0.0;
    double error = 0.0;
    double resolvedCommand = 0.0; //Variable for ending result
    double cumError = 0.0; //Variable for integration
    double prevError = 0.0; //Variable for differentiation
    double dError = 0.0; //Also a variable for differentiation

    PIDController(double pConst, double iConst, double dConst) //Constructor
    {
        kP = pConst;
        kI = iConst;
        kD = dConst;
    }

    double getError(double command, double actual)
    /*
    Returns the current error.
    */
    {
        return command - actual;
    }

    double getPGain(double errorNow)
    /*
    Returns the Proportional Gain
    */
    {
        return kP * errorNow;
    }

    double getIGain(double errorNow)
    /*
    Returns the integral term gain
    */
    {
        cumError += (errorNow)*.02;
        return kI * cumError;
    }

    double getDGain(double prevError, double errorNow)
    /*
    Returns the derivative term gain
    */
    {
        dError = (errorNow - prevError) / .02;
        return kD * dError;
    }

    void resetIntegralTerm()
    /*
    Resets the lower bound of integration. Must
    be called at the desired point by the user.
    */
    {
        cumError = 0.0;
    }

    double getResolvedCommand(double command, double actual)
    /*
    Calls the other functions and returns the resolved command to
    send to motors.
    */
    {
        error = getError(command, actual);
        pGain = getPGain(error);
        iGain = getIGain(error);
        dGain = getDGain(prevError, error);
        resolvedCommand = command + pGain + iGain + dGain;
        //printf("%f \n", command);
        prevError = error;
        return resolvedCommand;
    }
};