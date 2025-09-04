#include "components/SubArm.hpp"
#include "config.hpp"

SubArm::SubArm(SoftwareServo& arm_servo, SoftwareServo& claw_servo)
    : arm(arm_servo), claw(claw_servo) {
        // SoftwareServoはコンストラクタで初期化されるため、init()呼び出しは不要です。
        dropArm();
        openClaw(); // 安全のため、初期状態ではクローを開いておきます。
    }

void SubArm::liftArm() {
    arm.setAngleDeg(SubArmConfig::ARM_LIFT_ANGLE_DEG);
}
void SubArm::dropArm() {
    arm.setAngleDeg(SubArmConfig::ARM_DROP_ANGLE_DEG);
}

void SubArm::openClaw() {
    claw.setAngleDeg(SubArmConfig::CLAW_OPEN_ANGLE_DEG);
}
void SubArm::closeClaw() {
    claw.setAngleDeg(SubArmConfig::CLAW_CLOSE_ANGLE_DEG);
}
