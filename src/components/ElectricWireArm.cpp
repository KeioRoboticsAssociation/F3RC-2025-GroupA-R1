#include "components/ElectricWireArm.hpp"
#include "config.hpp"

ElectricWireArm::ElectricWireArm(DCMotor& motor) : motor(motor) {}

void ElectricWireArm::extend() {
    motor.setDuty(ElectricWireArmConfig::EXTEND_SPEED);
}
void ElectricWireArm::retract() {
    motor.setDuty(ElectricWireArmConfig::RETRACT_SPEED);
}
void ElectricWireArm::stop() {
    motor.setDuty(0.0);
}
