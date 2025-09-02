#ifndef ELECTRICWIREARM_HPP
#define ELECTRICWIREARM_HPP

#include <mbed.h>
#include "drivers/DCMotor.hpp"

class ElectricWireArm {
public:
    ElectricWireArm(DCMotor& motor);
    void extend();
    void retract();
    void stop();
private:
    DCMotor& motor;
};

#endif