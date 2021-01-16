
#include "WaterSensor.h"

WaterSensor::WaterSensor(uint8_t inputPin){
  waterSensorPin = inputPin;
  pinMode(inputPin, INPUT);
}

float WaterSensor::Read(){
  return analogRead(waterSensorPin);
}
