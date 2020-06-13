#include "main.h"

//Individual motor set up. No chassis is made. Hence the reversals of the right side.
Motor dtLF(11, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor dtLB(19, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor dtRF(2, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
Motor dtRB(10, true, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

//Creating motor groups per side
MotorGroup leftDT({dtLF, dtLB});
MotorGroup rightDT({dtRF, dtRB});

//Creating one motor group for full chassis
//essentially only for straights in auto.
MotorGroup chassis({dtLF, dtLB, dtRF, dtRB});