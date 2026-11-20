#include "Arduino.h"
#include "miniBeastV1.h"

#define RM_DIR 13
#define RM_PWM 11
#define LM_DIR 12
#define LM_PWM 10
#define TP A3 //Trimpot
#define UL1 8 //User Led1
#define UL2 9 //User Led2


//String XMotionReadString; 


Movement::Movement(){
	pinMode(RM_DIR, OUTPUT);
	pinMode(RM_PWM, OUTPUT);
	pinMode(LM_DIR, OUTPUT);
	pinMode(LM_PWM, OUTPUT);
	pinMode(UL1, OUTPUT);
	pinMode(UL2, OUTPUT);
	pinMode(TP,INPUT);
}

void Movement::SETUP(){

}

void Movement::UserLed1(int Time){
	digitalWrite(UL1,HIGH);
	delay(Time);
	digitalWrite(UL1,LOW);
	delay(Time);
}

void Movement::UserLed2(int Time){
	digitalWrite(UL2,HIGH);
	delay(Time);
	digitalWrite(UL2,LOW);
	delay(Time);
}

void Movement::speedM1M2(int16_t speed2, int16_t speed1) {
    // 1. Constrain to standard 8-bit PWM limits to prevent overflow
    speed1 = constrain(speed1,-100,100);
    speed2 = constrain(speed2,-100,100);
    speed1 = map(speed1, -100, 100, -255, 255);
    speed2 = map(speed2, -100, 100, -255, 255);
    Serial.println(speed2);
    Serial.println(speed1);

    // 2. Motor 1 (Right Motor)
    if (speed1 >= 0) {
        digitalWrite(RM_DIR, HIGH);
        analogWrite(RM_PWM, abs(speed1));
    } else {
        digitalWrite(RM_DIR, LOW);
        analogWrite(RM_PWM, abs(speed1)); // Negate to get positive PWM
    }

    // 3. Motor 2 (Left Motor)
    if (speed2 >= 0) {
        digitalWrite(LM_DIR, HIGH);
        analogWrite(LM_PWM, abs(speed2));
    } else {
        digitalWrite(LM_DIR, LOW);
        analogWrite(LM_PWM, abs(speed2));
    }
}

/*void Movement::S(){
   analogWrite(RM_PWM, 0);
   analogWrite(LM_PWM, 0);
   
}*/
void Movement::MotorControl(int RightMotorPwm, int LeftMotorPwm) {

  if (RightMotorPwm <= 0) {
    RightMotorPwm = abs(RightMotorPwm);
    digitalWrite(RM_DIR, LOW);
    analogWrite(RM_PWM, RightMotorPwm);
  }
  else {
    digitalWrite(RM_DIR, HIGH);
    analogWrite(RM_PWM, RightMotorPwm);
  }
  if (LeftMotorPwm <= 0) {
    LeftMotorPwm = abs(LeftMotorPwm);
    digitalWrite(LM_DIR, LOW);
    analogWrite(LM_PWM, LeftMotorPwm);
  }
  else {
    digitalWrite(LM_DIR, HIGH);
    analogWrite(LM_PWM, LeftMotorPwm);
  }
}


int Movement::Trimpot(){
	return analogRead(TP);
}


void Movement::ToggleLeds(int Time){	
	digitalWrite(UL1,HIGH);
	digitalWrite(UL2,LOW);
	digitalWrite(UL2,HIGH);
	digitalWrite(UL1,LOW);
	digitalWrite(UL1,LOW);
	digitalWrite(UL2,LOW);	
}


void Movement::CounterLeds(int Time, int countx){
for (int i=0; i < countx; i++){ // 
  movement.ToggleLeds(Time/2); // 
 }
}

void Movement::LipoCutOff(int Cell){

}

float Movement::VoltageIn(){
    return 0.0;
}

byte Movement::mode(){
    return 0;
}

bool Movement::GetButton(){
    return false;
}

Movement movement = Movement();