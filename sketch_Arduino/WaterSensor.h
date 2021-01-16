#ifndef Water_Sensor
#define Water_Sensor
#include <Arduino.h>

class WaterSensor
{
private:
uint8_t waterSensorPin;

public:

WaterSensor(uint8_t inputPin);

float Read();
};
#endif
