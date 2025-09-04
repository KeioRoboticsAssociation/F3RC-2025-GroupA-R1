#include <mbed.h>
#include <stdio.h>
#include <array>
#include <cmath>
#include "controller/Controller.hpp"
#include "components/SubArm.hpp"
#include "components/drivetrain/DriveTrain.hpp"
#include "drivers/DCMotor.hpp"
#include "drivers/SoftwareServo.hpp" // ServoMotorの代わりにSoftwareServoをインクルード
#include "components/ElectricWireArm.hpp"
#include "config.hpp"

asm(".global _printf_float"); // printfでfloatを使えるようにする

int main()
{
    DCMotor dc1(PwmOutPins::OMUNI_MOTOR1_PWM, DigitalOutPins::OMUNI_MOTOR1_DIR);
    DCMotor dc2(PwmOutPins::OMUNI_MOTOR2_PWM, DigitalOutPins::OMUNI_MOTOR2_DIR);
    DCMotor dc3(PwmOutPins::OMUNI_MOTOR3_PWM, DigitalOutPins::OMUNI_MOTOR3_DIR);
    DCMotor dc4(PwmOutPins::PSEUDO_SERVO1_PWM, DigitalOutPins::PSEUDO_SERVO1_DIR);

    // サーボモーターのセットアップ (SoftwareServoを使用)
    SoftwareServo servo1(PwmOutPins::SERVO1_PWM);
    SoftwareServo servo2(PwmOutPins::SERVO2_PWM);

    // wire armのセットアップ
    ElectricWireArm wire_arm(dc4);

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

        // コントローラーの入力値を変数に格納して可読性を向上
        const float move_x = joy.rStickX(); // 横移動
        const float move_y = joy.rStickY(); // 縦移動
        const bool turn_l_pressed = joy.L2();      // 左旋回
        const bool turn_r_pressed = joy.R2();      // 右旋回
        drive_train.move(move_x, move_y, turn_l_pressed, turn_r_pressed);

        if (joy.R1())
        {
            drive_train.changeToHighSpeedMode();
            printf("high speed mode\n");
        }
        else if (joy.L1())
        {
            drive_train.changeToLowSpeedMode();
            printf("low speed mode\n");
        }

        if (joy.dpadUp())
        {
            wire_arm.extend();
            printf("extending\n");
            
        }
        else if (joy.dpadDown())
        {
            wire_arm.retract();
            printf("retracting\n");
        } else {
            wire_arm.stop();
        }
   

        // SubArmのサーボモーター制御
        if (joy.triangle())
        {
            servo1.setAngleDeg(0); // 角度は要調整
            printf("lifting arm\n");
        }
        else if (joy.cross())
        {
            servo1.setAngleDeg(90); // 角度は要調整
            printf("dropping arm\n");
        }

        // SubArmのクロー制御
        if (joy.circle())
        {
            servo2.setAngleDeg(0); // 角度は要調整
            printf("opening claw\n");
        }
        else if (joy.square())
        {
            servo2.setAngleDeg(90); // 角度は要調整
            printf("closing claw\n");
        }
        
        // 100ms待機
        wait_us(100000);
    }
}
