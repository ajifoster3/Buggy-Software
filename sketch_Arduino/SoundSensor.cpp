
#include "SoundSensor.h"

SoundSensor::SoundSensor(uint8_t inputPin){
  soundSensorPin = inputPin;
  pinMode(inputPin, INPUT);
}

float SoundSensor::Read(){
  return analogRead(soundSensorPin);
}
