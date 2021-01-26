#ifndef Water_Sensor
#define Water_Sensor
#include <Arduino.h>

class WaterSensor
{
private:
//Pin for water sensor
uint8_t waterSensorPin;

public:
//constructor
WaterSensor(uint8_t inputPin);

//reads and returns waterSensor Data
float Read();
};
#endif
