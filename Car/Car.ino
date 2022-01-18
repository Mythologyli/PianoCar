#include <Arduino.h>

#include "moveCar.h"  //轮胎运动库
#include "servoCar.h" //舵机库

Move move;   //轮胎运动实例
Servo servo; //舵机实例

//*****************************************宏函数*****************************************
#define PLAY_EMPTY delay(1700)
#define PLAY_DO Play(104)
#define PLAY_RE Play(103)
#define PLAY_MI Play(102)
#define PLAY_FA Play(101)
#define PLAY_SOL Play(105)
#define PLAY_LA Play(106)
#define PLAY_SI Play(107)

//***************************************************************************************

//****************************************全局变量****************************************
// GND Pins
const uint8_t gnd_pins[8] = {12, 13, 32, 33, 34, 35, 36, 37};

//***************************************************************************************

//****************************************自定函数****************************************
//设置接口低电平作为额外地
void SetGNDPins(void);

//弹奏一个音
void Play(int num);

//碰撞传感器（开关）判断是否闭合
bool IsPushed(void);

//***************************************************************************************

void setup()
{
    SetGNDPins();

    move.Stop();
    servo.BeginTransmit();

    Serial.begin(9600);
    Serial2.begin(9600);

    Serial.write("start\n");

    while (!IsPushed())
        ;

    servo.Reset();

    unsigned long time = millis();
    for (int i = 0; i < 3; i++)
    {
        move.Forward(0.2);

        char ch;

        do
        {
            ch = Serial2.read();
        } while (ch == -1 || millis() - time < 2000);

        move.Stop();

        for (int i = 0; i < 1; i++)
        {
            PLAY_DO;
            PLAY_DO;
            PLAY_SOL;
            PLAY_SOL;
            PLAY_LA;
            PLAY_LA;
            PLAY_SOL;
            PLAY_EMPTY;
            PLAY_FA;
            PLAY_FA;
            PLAY_MI;
            PLAY_MI;
            PLAY_RE;
            PLAY_RE;
            PLAY_DO;
            // PLAY_EMPTY;
        }

        servo.Reset();
        delay(1700);
        time = millis();
    }

    while (1)
    {
    }
}

void loop()
{
}

//设置接口低电平作为额外地
void SetGNDPins(void)
{
    uint8_t pin_num = sizeof(gnd_pins) / sizeof(uint8_t);

    for (uint8_t i = 0; i < pin_num; i++)
    {
        pinMode(gnd_pins[i], OUTPUT);
        digitalWrite(gnd_pins[i], LOW);
    }
}

//弹奏一个音
void Play(int num)
{
    servo.RunActionGroup(num, 1);
    delay(1700);
}

//碰撞传感器（开关）判断是否闭合
bool IsPushed(void)
{
    int button_val = digitalRead(2);

    if (button_val == HIGH)
        return true;
    else
        return false;
}
