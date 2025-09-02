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

namespace ControllerConfig
{
    constexpr PinName tx = PB_10;
    constexpr PinName rx = PC_5;
    constexpr int BAUD_RATE = 115200;
}

namespace DriveConfig
{
    constexpr float WHEEL_RAD = 100.f;
    constexpr float TREAD_RAD = 100.f;

    // ここの値は要検証
    constexpr float HIGH_SPEED_RATIO = 1.f; // 高速モード [m/s]
    constexpr float LOW_SPEED_RATIO = 0.3f; // 低速モード [m/s]
    // 旋回速度の最大値（モードの影響無し）
    constexpr float TURN_SPEED = 1.f; // [rad/s]
}
=======
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
    constexpr PinName SERVO2_PWM        = PA_10;     // サーボ用PWM (Tim2)
}

namespace ControllerConfig
{
    constexpr int BAUD_RATE = 115200;
}

namespace DriveConfig
{
    constexpr float WHEEL_RAD = 100.f;
    constexpr float TREAD_RAD = 100.f;

    // ここの値は要検証
    constexpr float HIGH_SPEED_RATIO = 1.f; // 高速モード [m/s]
    constexpr float LOW_SPEED_RATIO = 0.3f; // 低速モード [m/s]
    // 旋回速度の最大値（モードの影響無し）
    constexpr float TURN_SPEED = 1.f; // [rad/s]
}
