#ifndef SERVOCAR_H
#define SERVOCAR_H

#include <Arduino.h>

//与舵机控制板连接串口
//使用 Mega 板 18 19 作为串口通信端口
#define SERVO_SERIAL_NUM Serial1

//与舵机控制板串口通信波特率
#define SERVO_BAUD_RATE 9600

//动作组
#define ACTION_RESET_NUM 99

//默认动作组速度
#define SERVO_NORMAL_SPEED 1.0

class Servo
{
public:
    Servo();

    static void BeginTransmit(unsigned long baud_rate = SERVO_BAUD_RATE); //打开串口

    static void MoveServo(uint8_t servo_id, uint16_t position, uint16_t time); //控制单个舵机转动

    static void RunActionGroup(uint8_t action_num, uint16_t times);   //运行指定动作组
    static void StopActionGroup(void);                                //停止动作组运行
    static void SetActionGroupSpeed(uint8_t action_num, float speed); //设定指定动作组的运行速度
    static void SetAllActionGroupSpeed(float speed);                  //设置所有动作组的运行速度

    static void Reset(float speed = SERVO_NORMAL_SPEED);        //恢复初始状态，指定速度
    static void StopAndReset(float speed = SERVO_NORMAL_SPEED); //停止舵机并恢复初始状态，指定速度

private:
    static HardwareSerial *SerialX;
};

#endif
