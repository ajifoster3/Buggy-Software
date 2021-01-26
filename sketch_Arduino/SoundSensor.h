#ifndef Sound_Sensor
#define Sound_Sensor
#include <Arduino.h>

class SoundSensor
{
private:
//Pin for soundSensor
uint8_t soundSensorPin;

public:
//constructor
SoundSensor(uint8_t inputPin);

//reads and returns soundsensor data
float Read();
};
#endif
