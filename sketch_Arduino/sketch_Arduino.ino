#define waterSensorPin A8 
#define soundSensorPin A15
#define servoMotorPin  10
#include "WaterSensor.h"
#include "SoundSensor.h"
#include "MotorControl.h"
#include <Servo.h>


boolean isServoExtended = 0;
Servo servo;
MotorControl mc = MotorControl(12, 3, 13, 11);
WaterSensor ws = WaterSensor(waterSensorPin);
SoundSensor ss = SoundSensor(soundSensorPin);

void ToggleServo();
void ExtendServo();
void RetractServo();



void setup() {
  Serial.begin(9600);
  
 
  
  servo.attach(servoMotorPin);

}

void loop() {
    Serial.print(ss.Read());
    Serial.print(",");
    Serial.println(ws.Read());
    

  if (Serial.available()) {
    String value = "." + Serial.readStringUntil('\n');
    if (value.indexOf("forward") > 0) {
        mc.Forward();
    } else if (value.indexOf("backward") > 0) {
        mc.Backward();
    }else if (value.indexOf("left") > 0) {
        mc.Left();
    }else if (value.indexOf("right") > 0) {
        mc.Right();
    }else if (value.indexOf("stop") > 0) {
        mc.Stop();
    }else if (value.indexOf("toggle") > 0) {
      ToggleServo();
    }
  }

  delay(500);
}

void ToggleServo() {
  if (isServoExtended) {
    RetractServo();
  } else {
    ExtendServo();
  }
}
void ExtendServo() {
  servo.write(150);
  isServoExtended = 1;
};
void RetractServo() {
  servo.write(0);
  isServoExtended = 0;
};
