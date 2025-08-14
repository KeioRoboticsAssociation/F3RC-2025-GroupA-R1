#pragma once
#include "Wheel.hpp"
#include "drivers/DCMotor.hpp"

// N: 車輪の数
template <int N>
class WheelController
{
public:
    WheelController(const std::array<WheelConfig, N> &wheel_configs, const std::array<DCMotor *, N> &motors, float max_duty = 1.f)
        : motors(motors), max_duty(max_duty)
    {
        for (int i = 0; i < N; i++)
        {
            wheel_vectors[i] = getWheelVector(wheel_configs[i]);
        }

        for (int i = 0; i < N; i++)
        {
            motors[i]->setDuty(0.f);
        }
    }

    void setDuty(Twist twist)
    {
        std::array<float, N> speeds = twistToMotorSpeeds(twist);

        for (int i = 0; i < N; i++)
        {
            motors[i]->setDuty(speeds[i]); // モーターに速度を設定
        }
    }

    std::array<float, N> twistToMotorSpeeds(const Twist twist)
    {
        std::array<float, N> speeds;
        float dec_ratio = 1.0; // 速度の減衰比

        for (int i = 0; i < N; i++)
        {
            speeds[i] = getWheelSpeedRelative(twist, wheel_vectors[i]); // 車輪の速度を計算
            if (fabs(speeds[i]) > max_duty)
            {
                dec_ratio = fmin(dec_ratio, max_duty / fabs(speeds[i])); // 速度が最大速度を超えた場合、減衰比を更新
            }
        }

        for (int i = 0; i < N; i++)
        {
            speeds[i] = dec_ratio * speeds[i]; // 速度を減衰
        }

        return speeds;
    }

private:
    std::array<DCMotor *, N> motors;
    float max_duty;
    std::array<WheelVector, N> wheel_vectors;
};
