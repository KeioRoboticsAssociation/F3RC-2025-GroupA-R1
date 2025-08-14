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

    inline float rStickX()
    {
        return r_stick[0];
    };
    inline float rStickY()
    {
        return r_stick[1];
    };
    inline float lStickX()
    {
        return l_stick[0];
    };
    inline float lStickY()
    {
        return l_stick[1];
    };
    inline bool dpadUp()
    {
        return dpad == 1;
    };
    inline bool dpadDown()
    {
        return dpad == 2;
    };
    inline bool dpadRight()
    {
        return dpad == 4;
    };
    inline bool dpadLeft()
    {
        return dpad == 8;
    };
    inline bool cross()
    {
        return button[0] == 1;
    };
    inline bool circle()
    {
        return button[1] == 1;
    };
    inline bool square()
    {
        return button[2] == 1;
    };
    inline bool triangle()
    {
        return button[3] == 1;
    };
    inline bool L1()
    {
        return button[4] == 1;
    };
    inline bool R1()
    {
        return button[5] == 1;
    };
    inline bool L2()
    {
        return button[6] == 1;
    };
    inline bool R2()
    {
        return button[7] == 1;
    };

    UnbufferedSerial esp;

private:
    void readEsp()
    {
        // 割り込み関数
        static int i = 0;
        esp.read(buf, 2);

        // 1文字ずつ読む
        if (i >= 64)
        {
            i = 0;
            memset(str, '\0', sizeof(str));
        }

        if (buf[0] == '\n')
        {
            // 改行コードが来たら
            i = 0;

            // 受信したデータを表示
            // printf("recv: %s\n", str);

            int data[6];
            sscanf(str, "%d %d %d %d %d %d\n", &data[0], &data[1], &data[2], &data[3], &data[4], &data[5]);

            r_stick[0] = data[0] / 512.f;
            r_stick[1] = data[1] / 512.f;
            l_stick[0] = data[2] / 512.f;
            l_stick[1] = data[3] / 512.f;
            dpad = data[4];
            for (int j = 0; j < 12; j++)
            {
                button[j] = (data[5] & (1 << j)) >> j;
            }
            memset(str, '\0', sizeof(str));
        }
        else
        {
            // 改行コードが来るまで
            str[i] = buf[0];
            i++;
        }
    }

    char buf[2];
    char str[64];
    bool button[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int dpad = 0;
    float r_stick[2] = {0.0, 0.0};
    float l_stick[2] = {0.0, 0.0};
};
