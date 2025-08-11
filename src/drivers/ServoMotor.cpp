#include "../include/drivers/ServoMotor.hpp"
#include <mbed.h>


ServoMotor::ServoMotor(PinName pwm_pin) : pwm(pwm_pin) {
}

void ServoMotor::init() {
    pwm.period_us(20000); // 20msの周期
}

void ServoMotor::setAngleDeg(float degrees) {
    if (degrees < MIN_ANGLE) {
        degrees = MIN_ANGLE;
    } else if (degrees > MAX_ANGLE) {
        degrees = MAX_ANGLE;
    }
    float pulseWidth_us = MIN_PULSE_WIDTH + degrees / MAX_ANGLE * (MAX_PULSE_WIDTH - MIN_PULSE_WIDTH);
    pwm.pulsewidth_us(pulseWidth_us); // パルス幅を設定
}