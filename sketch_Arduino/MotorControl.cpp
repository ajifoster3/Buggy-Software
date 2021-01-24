
#include "MotorControl.h"

MotorControl::MotorControl(uint8_t leftDirection, uint8_t leftSpeed, uint8_t rightDirection, uint8_t rightSpeed){
  LeftDirection = leftDirection;
  LeftSpeed = leftSpeed;
  RightDirection = rightDirection;
  RightSpeed = rightSpeed;
}

void MotorControl::Forward(){
      digitalWrite(LeftDirection, LOW); 
      analogWrite(LeftSpeed, 255);   
      digitalWrite(RightDirection, HIGH);  
      analogWrite(RightSpeed, 225);   
}
void MotorControl::Backward(){
      digitalWrite(LeftDirection, HIGH); 
      analogWrite(LeftSpeed, 255);  
      digitalWrite(RightDirection, LOW);  
      analogWrite(RightSpeed, 225);    
}
void MotorControl::Stop(){
      digitalWrite(LeftDirection, LOW); 
      analogWrite(LeftSpeed, 0);   
      digitalWrite(RightDirection, HIGH);  
      analogWrite(RightSpeed, 0);    
}
void MotorControl::Left(){
      digitalWrite(LeftDirection, LOW); 
      analogWrite(LeftSpeed, 255);  
      digitalWrite(RightDirection, HIGH);  
      analogWrite(RightSpeed, 50);    
}
void MotorControl::Right(){
      digitalWrite(LeftDirection, LOW); 
      analogWrite(LeftSpeed, 50);   
      digitalWrite(RightDirection, HIGH);  
      analogWrite(RightSpeed, 225);    
}
