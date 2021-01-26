#define waterSensorPin A8
#define soundSensorPin A15
#define servoMotorPin  10
#define motorLeftDirection 12
#define motorLeftSpeed 3
#define motorRightDirection 13
#define motorRightSpeed 11
#include "WaterSensor.h"
#include "SoundSensor.h"
#include "MotorControl.h"
#include <Servo.h>

//Keeps track of Servo State
boolean isServoExtended = 0;
Servo servo;
//Object Initalisation
MotorControl mc = MotorControl(motorLeftDirection,
                               motorLeftSpeed,
                               motorRightDirection,
                               motorRightSpeed);
WaterSensor ws = WaterSensor(waterSensorPin);
SoundSensor ss = SoundSensor(soundSensorPin);

//Declare Servo functionallity
//Implementation at bottom of file
//Servo didn't work in a class?
void ToggleServo();
void ExtendServo();
void RetractServo();



void setup() {
  //Begin Serial for UART communication
  Serial.begin(9600);
  //Attach servo
  servo.attach(servoMotorPin);

}

void loop() {
  //Read Sensor data and comma seperate values
  Serial.print(ss.Read());
  Serial.print(",");
  Serial.println(ws.Read());

  //If there is serial data to read handle it
  if (Serial.available()) {
    String value = "." + Serial.readStringUntil('\n');
    if (value.indexOf("forward") > 0) {
      mc.Forward();
    } else if (value.indexOf("backward") > 0) {
      mc.Backward();
    } else if (value.indexOf("left") > 0) {
      mc.Left();
    } else if (value.indexOf("right") > 0) {
      mc.Right();
    } else if (value.indexOf("stop") > 0) {
      mc.Stop();
    } else if (value.indexOf("toggle") > 0) {
      ToggleServo();
    }
  }

  delay(500);
}

//Raises or lowers servo depending on current state
void ToggleServo() {
  if (isServoExtended) {
    RetractServo();
  } else {
    ExtendServo();
  }
}
//Lowers Servo
void ExtendServo() {
  servo.write(150);
  isServoExtended = 1;
};
//Raises Servo
void RetractServo() {
  servo.write(0);
  isServoExtended = 0;
};
