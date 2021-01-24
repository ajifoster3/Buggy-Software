#ifndef Motor_Control
#define Motor_Control
#include <Arduino.h>

class MotorControl
{
private:
uint8_t LeftDirection;
uint8_t LeftSpeed;
uint8_t RightDirection;
uint8_t RightSpeed;

public:

MotorControl(uint8_t leftDirection, uint8_t leftSpeed, uint8_t rightDirection, uint8_t rightSpeed);

void Forward();
void Backward();
void Stop();
void Left();
void Right();
};
#endif
