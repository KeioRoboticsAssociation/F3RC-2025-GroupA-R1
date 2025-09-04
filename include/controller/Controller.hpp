#pragma once
#include <mbed.h>

class Controller
{
public:
    Controller(PinName tx, PinName rx, int baudrate)
        : esp(tx, rx, baudrate)
    {
        esp.attach(callback(this, &Controller::readEsp), UnbufferedSerial::RxIrq);
    }

    inline float lStickX() { return -(float)data[0] / STICK_NORMALIZE_FACTOR; };
    inline float lStickY() { return (float)data[1] / STICK_NORMALIZE_FACTOR; };
    inline float rStickX() { return -(float)data[2] / STICK_NORMALIZE_FACTOR; };
    inline float rStickY() { return (float)data[3] / STICK_NORMALIZE_FACTOR; };
    inline bool dpadUp() { return data[4] == 1; };
    inline bool dpadDown() { return data[4] == 2; };
    inline bool dpadRight() { return data[4] == 4; };
    inline bool dpadLeft() { return data[4] == 8; };
    inline bool cross() { return ((data[5] >> 0) & 1) == 1; };
    inline bool circle() { return ((data[5] >> 1) & 1) == 1; };
    inline bool square() { return ((data[5] >> 2) & 1) == 1; };
    inline bool triangle() { return ((data[5] >> 3) & 1) == 1; };
    inline bool L1() { return ((data[5] >> 4) & 1) == 1; };
    inline bool R1() { return ((data[5] >> 5) & 1) == 1; };
    inline bool L2() { return ((data[5] >> 6) & 1) == 1; };
    inline bool R2() { return ((data[5] >> 7) & 1) == 1; };

    UnbufferedSerial esp;

private:
    void readEsp()
    {
        char buf;
        esp.read(&buf, 1);

        str[str_pos] = buf;
        str_pos++;

        if (str_pos >= 64)
        {
            // 64文字以上になったらリセット
            str_pos = 0;
            memset(str, 0, sizeof(str));
            return;
        }

        if (buf != '\n')
        {
            return;
        }

        // 改行コードが来たら
        str_pos = 0;
        sscanf(str, "%d %d %d %d %d %d\n", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5]);
        memset(str, 0, sizeof(str));
    }

    static constexpr float STICK_NORMALIZE_FACTOR = 512.f;
    char str[64];
    int str_pos = 0;
    int data[6]{}; // 0で初期化
};
