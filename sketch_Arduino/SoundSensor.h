#ifndef Sound_Sensor
#define Sound_Sensor
#include <Arduino.h>

class SoundSensor
{
private:
uint8_t soundSensorPin;

public:

SoundSensor(uint8_t inputPin);

float Read();
};
#endif
