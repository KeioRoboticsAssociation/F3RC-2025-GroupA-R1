#pragma once
#include <mbed.h>

class ServoMotor{
    public:
        ServoMotor(PinName pwm_pin);
        void init();
        void setAngleDeg(float degrees);

    private:
        PwmOut pwm;
        static const int MIN_PULSE_WIDTH = 500;  // 0度に対応するパルス幅 (マイクロ秒)
        static const int MAX_PULSE_WIDTH = 2500; // 180度に対応するパルス幅 (マイクロ秒)
        static constexpr float MIN_ANGLE = 0.0f;
        static constexpr float MAX_ANGLE = 180.0f;

};


        
