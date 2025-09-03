#include <mbed.h>
#include <stdio.h>
#include <array>
#include <cmath>
#include "controller/Controller.hpp"
#include "components/drivetrain/DriveTrain.hpp"
#include "drivers/ServoMotor.hpp"
#include "drivers/DCMotor.hpp"

asm(".global _printf_float"); // printfでfloatを使えるようにする

int main()
{
    DCMotor dc1(PwmOutPins::OMUNI_MOTOR1_PWM, DigitalOutPins::OMUNI_MOTOR1_DIR);
    DCMotor dc2(PwmOutPins::OMUNI_MOTOR2_PWM, DigitalOutPins::OMUNI_MOTOR2_DIR);
    DCMotor dc3(PwmOutPins::OMUNI_MOTOR3_PWM, DigitalOutPins::OMUNI_MOTOR3_DIR);

    // サーボモーターのセットアップ
    ServoMotor servo1(PwmOutPins::SERVO1_PWM);
    ServoMotor servo2(PwmOutPins::SERVO2_PWM);
    servo1.init();
    servo2.init(); 

    std::array<WheelConfig, 3> config = {
        WheelConfig{
            .wheel_radius = DriveConfig::WHEEL_RAD, // ホイール半径
            .wheel_x = 0.0,                         // ホイールのx座標
            .wheel_y = DriveConfig::TREAD_RAD,      // ホイールのy座標
            .wheel_theta = M_PI                     // ホイールの向き
        },
        WheelConfig{
            .wheel_radius = DriveConfig::WHEEL_RAD,
            .wheel_x = -std::sqrt(3.0f) / 2 * DriveConfig::TREAD_RAD,
            .wheel_y = -(float)0.5 * DriveConfig::TREAD_RAD,
            .wheel_theta = 5 * M_PI / 3},
        WheelConfig{
            .wheel_radius = DriveConfig::WHEEL_RAD,
            .wheel_x = +std::sqrt(3.0f) / 2 * DriveConfig::TREAD_RAD,
            .wheel_y = -(float)0.5 * DriveConfig::TREAD_RAD,
            .wheel_theta = M_PI / 3}};

    WheelController<3> wheel_controller(config, {&dc1, &dc2, &dc3});

    Controller joy(ControllerConfig::tx, ControllerConfig::rx, ControllerConfig::BAUD_RATE);
    DriveTrain<3> drive_train(wheel_controller);

    while (1)
    {
        // printf("%5.2f %5.2f %5.2f %5.2f %d %d %d %d %d %d %d %d %d %d %d %d\n",
        //        joy.rStickX(),   // 左スティックX(左-1.0~1.0右)
        //        joy.rStickY(),   // 左スティックY(上-1.0~1.0下)
        //        joy.lStickX(),   // 右スティックX(左-1.0~1.0右)
        //        joy.lStickY(),   // 右スティックY(上-1.0~1.0下)
        //        joy.dpadUp(),    // 十字キー上
        //        joy.dpadDown(),  // 十字キー下
        //        joy.dpadRight(), // 十字キー右
        //        joy.dpadLeft(),  // 十字キー左
        //        joy.cross(),     // ×
        //        joy.circle(),    // ○
        //        joy.square(),    // ⬜︎
        //        joy.triangle(),  // △
        //        joy.L1(),        // L1
        //        joy.R1(),        // R1
        //        joy.L2(),        // L2
        //        joy.R2());       // R2

        drive_train.move(joy.rStickX(), joy.rStickY(), joy.L2(), joy.R2());

        if (joy.R1())
        {
            drive_train.changeToHighSpeedMode();
        }
        else if (joy.L1())
        {
            drive_train.changeToLowSpeedMode();
        }

        // SubArmのサーボモーター制御
        // R1/L1は足回りの速度変更で使用しているため、別のボタンに変更します。
        // 例: △ボタンでサーボ1を90度、×ボタンで0度へ
        if (joy.triangle())
        {
            servo1.setAngleDeg(90);
        }
        else if (joy.cross())
        {
            servo1.setAngleDeg(0);
        }

        // R2/L2は足回りの旋回で使用しているため、別のボタンに変更します。
        // 例: ○ボタンでサーボ2を90度、□ボタンで0度へ
        if (joy.circle())
        {
            servo2.setAngleDeg(90);
        }
        else if (joy.square())
        {
            servo2.setAngleDeg(0);
        }
        wait_us(100000);
    }
}
