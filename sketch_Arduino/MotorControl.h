#ifndef Motor_Control
#define Motor_Control
#include <Arduino.h>

class MotorControl
{
private:
//Holds relevant pins for given tasks
uint8_t LeftDirection;
uint8_t LeftSpeed;
uint8_t RightDirection;
uint8_t RightSpeed;

public:
//Constructor
MotorControl(uint8_t leftDirection, uint8_t leftSpeed, uint8_t rightDirection, uint8_t rightSpeed);
//Movement functions for Buggy
void Forward();
void Backward();
void Stop();
void Left();
void Right();
};
#endif
