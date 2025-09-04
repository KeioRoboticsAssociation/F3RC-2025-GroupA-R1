#pragma once
#include <PinNames.h>



namespace DigitalOutPins
{
    constexpr PinName OMUNI_MOTOR1_DIR  = PC_10;     // オムニホイールDC1の方向
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
    constexpr PinName tx = PB_10;
    constexpr PinName rx = PC_5;
    constexpr int BAUD_RATE = 115200;
}

namespace DriveConfig
{
    constexpr float WHEEL_RAD = 100.f;
    constexpr float TREAD_RAD = 100.f;

    // ここの値は要検証
    // DriveTrain内で並進速度を計算する際の係数。
    // 1.0の場合、スティック最大入力でロボット中心の速度が TREAD_RAD [mm/s] となる。
    // 値を大きくすると、より高速に移動する。まずは5.0あたりで試すことを推奨。
    constexpr float HIGH_SPEED_RATIO = 5.f; // 高速モード時の速度係数 (無次元)
    constexpr float LOW_SPEED_RATIO = 1.5f; // 低速モード時の速度係数 (無次元)
    // 旋回速度の最大値（モードの影響無し）
    constexpr float TURN_SPEED = 1.f; // [rad/s]
}

namespace SubArmConfig
{
    // アームの角度 [deg]
    constexpr float ARM_LIFT_ANGLE_DEG = 0.0f;
    constexpr float ARM_DROP_ANGLE_DEG = 90.0f;

    // クローの角度 [deg]
    constexpr float CLAW_OPEN_ANGLE_DEG = 0.0f;
    constexpr float CLAW_CLOSE_ANGLE_DEG = 45.0f;
}

namespace ElectricWireArmConfig
{
    // ワイヤーアームのモーター出力（デューティ比, -1.0 ~ 1.0）
    // 0.5fでは摩擦に負けて動かない可能性があったため、少し出力を上げます。
    constexpr float EXTEND_SPEED = 0.7f;
    constexpr float RETRACT_SPEED = -0.7f;
}
