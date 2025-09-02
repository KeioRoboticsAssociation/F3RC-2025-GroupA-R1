#ifndef SUBARM_HPP
#define SUBARM_HPP

#include <mbed.h>
#include "drivers/ServoMotor.hpp"

class SubArm {
public:
    SubArm(ServoMotor& arm_servo, ServoMotor& claw_servo);
    void liftArm();
    void dropArm();
    void openClaw();
    void closeClaw();
private:
    ServoMotor& arm;
    ServoMotor& claw;
};

#endif