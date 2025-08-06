#pragma once
#include <PinNames.h>



namespace DigitalOutPins
{
    constexpr PinName OMUNI_MOTOR1_DIR  = PB_10;     // オムニホイールDC1の方向
    constexpr PinName OMUNI_MOTOR2_DIR  = PC_7 ;     // オムニホイールDC2の方向
    constexpr PinName OMUNI_MOTOR3_DIR  = PB_4 ;     // オムニホイールDC3の方向

    constexpr PinName PSEUDO_SERVO1_DIR = PB_9 ;     // 疑似サーボ用DC1の方向
    constexpr PinName PSEUDO_SERVO1_DIR = PB_6 ;     // 疑似サーボ用DC2の方向
}



namespace PwmOutPins
{
    constexpr PinName OMUNI_MOTOR1_PWM  = PA_8 ;     // オムニホイールDC1のPWM (Tim1)
    constexpr PinName OMUNI_MOTOR2_PWM  = PA_9 ;     // オムニホイールDC2のPWM (Tim1)
    constexpr PinName OMUNI_MOTOR3_PWM  = PA_10;     // オムニホイールDC3のPWM (Tim1)

    constexpr PinName PSEUDO_SERVO1_PWM = PA_6 ;     // 疑似サーボ用DC1のPWM (Tim3)
    constexpr PinName PSEUDO_SERVO1_PWM = PA_7 ;     // 疑似サーボ用DC2のPWM (Tim3)

    constexpr PinName SERVO_PWM         = PA_15;     // サーボ用PWM (Tim2)
}