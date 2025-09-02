#include "components/ElectricWireArm.hpp"

ElectricWireArm::ElectricWireArm(DCMotor& motor) : motor(motor) {}

void ElectricWireArm::extend() {
    motor.setDuty(0.2);
}
void ElectricWireArm::retract() {
    motor.setDuty(-0.2);
}
void ElectricWireArm::stop() {
    motor.setDuty(0.0);
}
