#pragma once
#include "Wheel.hpp"
#include "WheelController.hpp"
#include "controller/Controller.hpp"
#include "config.hpp"

// N: 車輪の数
template <int N>
class DriveTrain
{
public:
    DriveTrain(WheelController<N> &wheel_controller) : wheel_controller(wheel_controller), is_high_speed_mode(true) {}

    void move(float x, float y, bool L2, bool R2)
    {
        Twist twist = parseToTwist(x, y, L2, R2);
        wheel_controller.setDuty(twist);
    }

    void changeToHighSpeedMode()
    {
        is_high_speed_mode = true;
    }

    void changeToLowSpeedMode()
    {
        is_high_speed_mode = false;
    }

    WheelController<N> &wheel_controller;

private:
    // @return Twist xとyはDuty比
    Twist parseToTwist(float x, float y, bool L2, bool R2)
    {
        // ジョイスティックの入力値（-1.0 ~ 1.0の比率）を、ロボットの物理的な速度（mm/s, rad/s）に変換します。
        // 並進速度(vx, vy)の大きさが、回転速度(omega)による接線速度とおおよそ同じオーダーになるように、
        // ロボットの半径(TREAD_RAD)をスケーリング係数として使用します。
        // これにより、並進と回転の操作感が統一されます。
        const float linear_velocity_scaler = DriveConfig::TREAD_RAD * (is_high_speed_mode ? DriveConfig::HIGH_SPEED_RATIO : DriveConfig::LOW_SPEED_RATIO);

        // Twist構造体は物理的な速度を保持します (vx, vy: mm/s, omega: rad/s)
        Twist twist{
            .vx = x * linear_velocity_scaler,
            .vy = y * linear_velocity_scaler,
            .omega = 0.f
        };

        if (L2 && !R2)
        {
            // TURN_SPEEDは rad/s 単位の定数です
            twist.omega = DriveConfig::TURN_SPEED;
        }
        else if (!L2 && R2)
        {
            twist.omega = -DriveConfig::TURN_SPEED;
        }

        return twist;
    }
    bool is_high_speed_mode;
};
