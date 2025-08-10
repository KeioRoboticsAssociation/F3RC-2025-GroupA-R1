#pragma once
#include <PinNames.h>



namespace DigitalOutPins
{
    constexpr PinName OMUNI_MOTOR1_DIR  = PA_10;     // オムニホイールDC1の方向
    constexpr PinName OMUNI_MOTOR2_DIR  = PA_0 ;     // オムニホイールDC2の方向
    constexpr PinName OMUNI_MOTOR3_DIR  = PC_3 ;     // オムニホイールDC3の方向

    constexpr PinName PSEUDO_SERVO1_DIR = PC_2 ;     // 疑似サーボ用DC1の方向
}



namespace PwmOutPins
{
    constexpr PinName OMUNI_MOTOR1_PWM  = PA_15;     // オムニホイールDC1のPWM (Tim1)
    constexpr PinName OMUNI_MOTOR2_PWM  = PB_7 ;     // オムニホイールDC2のPWM (Tim1)
    constexpr PinName OMUNI_MOTOR3_PWM  = PA_1 ;     // オムニホイールDC3のPWM (Tim1)

    constexpr PinName PSEUDO_SERVO1_PWM = PB_0 ;     // 疑似サーボ用DC1のPWM (Tim3)

    constexpr PinName SERVO1_PWM        = PB_2 ;     // サーボ用PWM (Tim2)
    // PA_0 は OMUNI_MOTOR2_DIR で既に使用されているためピンが競合しています。
    // ハードウェアの仕様を確認し、利用可能なPWMピンに変更してください。ここでは例として PA_3 を使用します。
    constexpr PinName SERVO2_PWM        = PA_3 ;     // サーボ用PWM (Tim2)
}
