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
        float x_output = x;
        float y_output = y;
        if (is_high_speed_mode)
        {
            x_output *= DriveConfig::HIGH_SPEED_RATIO;
            y_output *= DriveConfig::HIGH_SPEED_RATIO;
        }
        else
        {
            x_output *= DriveConfig::LOW_SPEED_RATIO;
            y_output *= DriveConfig::LOW_SPEED_RATIO;
        }

        Twist twist{x_output, y_output, 0.f};

        if (L2 && !R2)
        {
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
