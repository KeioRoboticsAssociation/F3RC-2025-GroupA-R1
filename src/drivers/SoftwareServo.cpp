#include "drivers/SoftwareServo.hpp"

SoftwareServo::SoftwareServo(PinName pin) : _pin(pin) {
    _pin = 0;
    // Default to 90 degrees (1500 us)
    _pulsewidth_us = 1500;
    // Start the 20ms pulse cycle
    _ticker.attach(callback(this, &SoftwareServo::pulse), 20ms);
}

void SoftwareServo::setAngleDeg(float angle) {
    if (angle < 0.0f) angle = 0.0f;
    if (angle > 180.0f) angle = 180.0f;
    // Standard servo range: 0 deg -> 500us, 180 deg -> 2500us
    _pulsewidth_us = 500 + (int)(angle * (2000.0f / 180.0f));
}

void SoftwareServo::pulse() {
    _pin = 1;
    _timeout.attach_us(callback(this, &SoftwareServo::endPulse), _pulsewidth_us);
}

void SoftwareServo::endPulse() {
    _pin = 0;
}
