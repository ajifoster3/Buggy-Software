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
  servo1.attach(10);
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin


}

void loop() {
    Serial.print(ss.Read());
    Serial.print(",");
    Serial.println(ws.Read());
    

  if (Serial.available()) {
    String value = "." + Serial.readStringUntil('\n');
    if (value.indexOf("forward") > 0) {
      digitalWrite(12, LOW); //Establishes forward direction of Channel A
      analogWrite(3, 255);   //Spins the motor on Channel A at full speed

      
      digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
      analogWrite(11, 225);    //Spins the motor on Channel B at half speed
    } else if (value.indexOf("backward") > 0) {
     digitalWrite(12, HIGH); //Establishes forward direction of Channel A
      analogWrite(3, 255);   //Spins the motor on Channel A at full speed

      
      digitalWrite(13, LOW);  //Establishes backward direction of Channel B
      analogWrite(11, 225);    //Spins the motor on Channel B at half speed
    }else if (value.indexOf("left") > 0) {
    digitalWrite(12, LOW); //Establishes forward direction of Channel A
      analogWrite(3, 255);   //Spins the motor on Channel A at full speed
      digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
      analogWrite(11, 50);    //Spins the motor on Channel B at half speed

    }else if (value.indexOf("right") > 0) {
      digitalWrite(12, LOW); //Establishes forward direction of Channel A
      analogWrite(3, 50);   //Spins the motor on Channel A at full speed

      //Motor B backward @ half speed
      digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
      analogWrite(11, 225);    //Spins the motor on Channel B at half speed

    }
    else if (value.indexOf("stop") > 0) {
    digitalWrite(12, LOW); //Establishes forward direction of Channel A
      analogWrite(3, 0);   //Spins the motor on Channel A at full speed

      //Motor B backward @ half speed
      digitalWrite(13, HIGH);  //Establishes backward direction of Channel B
      analogWrite(11, 0);    //Spins the motor on Channel B at half speed
    }
    else if (value.indexOf("toggle") > 0) {
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
  servo1.write(150);
  isServoExtended = 1;
};
void RetractServo() {
  servo1.write(0);
  isServoExtended = 0;
};
