#pragma once
#include "mbed.h"

/**
 * @brief A class to control a servo motor using software-based PWM.
 * This uses a Ticker and DigitalOut to generate the pulse, avoiding hardware timer conflicts.
 */
class SoftwareServo {
public:
    SoftwareServo(PinName pin);
    void setAngleDeg(float angle);

private:
    void pulse();
    void endPulse();

    DigitalOut _pin;
    Ticker _ticker;
    Timeout _timeout;
    volatile int _pulsewidth_us;
};
