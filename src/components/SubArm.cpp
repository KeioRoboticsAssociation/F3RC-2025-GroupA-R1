#include "components/SubArm.hpp"

SubArm::SubArm(ServoMotor& arm_servo, ServoMotor& claw_servo)
    : arm(arm_servo), claw(claw_servo) {
        arm.init();
        claw.init();
        dropArm();
        closeClaw();
    }

void SubArm::liftArm() {
    arm.setAngleDeg(0.0f);
}
void SubArm::dropArm() {
    arm.setAngleDeg(90.0f);
}

void SubArm::openClaw() {
    claw.setAngleDeg(0.0f);
}
void SubArm::closeClaw() {
    claw.setAngleDeg(45.0f);
}
