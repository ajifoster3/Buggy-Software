#define waterSensorPin A0 // Attach Water sensor to Arduino Digital Pin 8
#define soundSensorPin A15
#include "WaterSensor.h"
#include "SoundSensor.h"
#include <Servo.h>

Servo servo1;

float val = 0;
int count = 0;
boolean isServoExtended = 0;
void ExtendServo();
void RetractServo();
void ToggleServo();

WaterSensor ws = WaterSensor(waterSensorPin);
SoundSensor ss = SoundSensor(soundSensorPin);

void setup() {
 Serial.begin(9600);
}

void loop() {
  Serial.print(ss.Read());
  Serial.print(",");
  Serial.println(ws.Read());
}




void ToggleServo(){
  if(isServoExtended){
    RetractServo();
  }else{
    ExtendServo();
  }
}
void ExtendServo(){
  servo1.write(150);
  isServoExtended = 1;
  };
void RetractServo(){
  servo1.write(0);
  isServoExtended = 0;
  };
