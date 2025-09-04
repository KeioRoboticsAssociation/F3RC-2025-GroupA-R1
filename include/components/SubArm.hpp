#ifndef SUBARM_HPP
#define SUBARM_HPP

#include <mbed.h>
#include "drivers/SoftwareServo.hpp"

class SubArm {
public:
    SubArm(SoftwareServo& arm_servo, SoftwareServo& claw_servo);
    void liftArm();
    void dropArm();
    void openClaw();
    void closeClaw();
private:
    SoftwareServo& arm;
    SoftwareServo& claw;
};

#endif