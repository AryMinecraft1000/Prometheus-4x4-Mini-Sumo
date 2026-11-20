#include <Arduino.h>
//#include <xmotionV3.h>
#include "headers/config.h"
#include "headers/flank.h"
//#include <Servo.h>
#include <miniBeastV1.h>


/**
 * A non-blocking timer check.
 * @param lastTime A reference to the static variable holding the start time.
 * @param duration The time to wait in milliseconds.
 * @return True if the time has elapsed, false otherwise.
 */
bool checkTimer(unsigned long &lastTime, unsigned long duration) {
  if (millis() - lastTime > duration) {
    lastTime = millis(); // Reset the timer for the next interval
    return true;
  }
  return false;
}

int LeftSensor = 2;
int MiddleLeftSensor = 1;
int MiddleRightSensor = A2;
int RightSensor = A4;

int LeftLine = 0;
int RightLine = A1;
int Start = A0;

int Led1 = 8;

int Dip1 = 5;
int Dip2 = 6;
int Dip3 = 7;

int ServoPin = 4;

int defaultTimer{1};
unsigned long timer1{};
unsigned long timer2{};
unsigned long timer3{};
unsigned long timer4{};
unsigned long timer5{};

unsigned long timer_pos7{};
unsigned long timer_pos8{};


unsigned long pos7_flag_start_timer = 0;
unsigned long pos8_flag_start_timer = 0;


bool pos7_flag{ false };
bool pos8_flag{ false };

bool zigzagLeft{ true };
bool runOnce{false};

// left1/right1 50 base speed ~180* turn at 250ms
//1 in movement is for +/-, 2 is for 0/+ , 3 is for agresive turn, 4 less agresive turn and 5 domestic turn
int8_t fullSpeed{40};
int8_t baseSpeed{30};
struct Speed{
    int8_t m1_Left1{-baseSpeed};
    int8_t m2_Left1{baseSpeed};
    int8_t m1_Left2{0};
    int8_t m2_Left2{baseSpeed};
    int8_t m1_Left3{baseSpeed / 4};
    int8_t m2_Left3{baseSpeed};
    int8_t m1_Left4{baseSpeed / 2};
    int8_t m2_Left4{baseSpeed};
    int8_t m1_Left5{baseSpeed / 1.5};
    int8_t m2_Left5{baseSpeed};
    int8_t m1_Right1{baseSpeed};
    int8_t m2_Right1{-baseSpeed};
    int8_t m1_Right2{baseSpeed};
    int8_t m2_Right2{0};
    int8_t m1_Right3{baseSpeed};
    int8_t m2_Right3{baseSpeed / 4};
    int8_t m1_Right4{baseSpeed};
    int8_t m2_Right4{baseSpeed / 2};
    int8_t m1_Right5{baseSpeed};
    int8_t m2_Right5{baseSpeed / 1.5};
    int8_t forward3{baseSpeed / 1.3};
    int8_t forward2{baseSpeed};
    int8_t forward1{fullSpeed};
    int8_t backwards1{fullSpeed};
    int8_t backwards2{fullSpeed /2};
};
Speed speed{};


    void left1(){
        movement.speedM1M2(speed.m1_Left1, speed.m2_Left1);
}
    void left2(){
        movement.speedM1M2(speed.m1_Left2, speed.m2_Left2);
}
    void left3(){
        movement.speedM1M2(speed.m1_Left3, speed.m2_Left3);
}
    void left4(){
        movement.speedM1M2(speed.m1_Left4, speed.m2_Left4);
}
    void left5(){
        movement.speedM1M2(speed.m1_Left5, speed.m2_Left5);
}
    void right1(){
        movement.speedM1M2(speed.m1_Right1, speed.m2_Right1);
}
    void right2(){
        movement.speedM1M2(speed.m1_Right2, speed.m2_Right2);
}
    void right3(){
        movement.speedM1M2(speed.m1_Right3, speed.m2_Right3);
}
    void right4(){
        movement.speedM1M2(speed.m1_Right4, speed.m2_Right4);
}
    void right5(){
        movement.speedM1M2(speed.m1_Right5, speed.m2_Right5);
}
    void forward1(){
        movement.speedM1M2(speed.forward1, speed.forward1 + (speed.forward1 / 6));
}
    void forward2(){
        movement.speedM1M2(speed.forward2, speed.forward2 + (speed.forward2 / 6));
}
    void forward3(){
        movement.speedM1M2(speed.forward3, speed.forward3 + (speed.forward3 / 6));
}
    void backwards1(){
        movement.speedM1M2(-speed.backwards1, -speed.backwards1);
}
    void backwards2(){
        movement.speedM1M2(-speed.backwards2, -speed.backwards2);
}

    void backwardsLeft(){
        movement.speedM1M2(-baseSpeed * 1 / 8, -baseSpeed * 1);
    }

    void backwardsRight(){
        movement.speedM1M2(-baseSpeed * 1, -baseSpeed * 1 / 8);
    }

    void stopMotors(){
        movement.speedM1M2(0, 0);
        delay(10);
}
   //     void Stop(){
    //        movement.S();
    //}



//bool os;

bool leftLineSaw{ false };
bool rightLineSaw{ false };

bool sideSaw{false};

enum Strategy {
    normal,
    flankS,
    allIn,
    lineTest,
    zigzag,
    suicide,
    err
};

Strategy selectedStrategy{ normal };
bool offValueDipSwitch{ true };//⚠️ cand switch-ul este in jos ⚠️ VERIFICA FOLOSIND FUNCTIA DE MAI JOS PENTRU A CITI VALOREA⚠️
bool onValueDipSwitch{ false };//⚠️ cand switch-ul este in sus

void printDipSwitch(){
  bool S[]{ digitalRead(Dip1), digitalRead(Dip2), digitalRead(Dip3)};
  Serial.print("Dip Switch 1: ");
  Serial.print(S[0]);
  Serial.println("");
  Serial.println("");
  Serial.print("Dip Switch 2: ");
  Serial.print(S[1]);
  Serial.println("");
  Serial.println("");
  Serial.print("Dip Switch 3: ");
  Serial.print(S[2]);
  Serial.println("");
  Serial.println("");

  //de-comenteaza delay-ul doar daca sunt probleme de citire
  //delay(300) 

}

//Servo myServo{};

void motorTest(){
    // Test Forward movements
    forward1();
    delay(500);
    stopMotors();
    delay(3000);
    
    forward2();
    delay(500);
    stopMotors();
    delay(3000);
    
    forward3();
    delay(500);
    stopMotors();
    delay(3000);

    // Test Left movements (1-5)
    left1();
    delay(250);
    stopMotors();
    delay(3000);
    
    left2();
    delay(400);
    stopMotors();
    delay(3000);
    
    left3();
    delay(500);
    stopMotors();
    delay(3000);
    
    left4();
    delay(500);
    stopMotors();
    delay(3000);
    
    left5();
    delay(500);
    stopMotors();
    delay(3000);

    // Test Right movements (1-5)
    right1();
    delay(250);
    stopMotors();
    delay(3000);
    
    right2();
    delay(400);
    stopMotors();
    delay(3000);
    
    right3();
    delay(500);
    stopMotors();
    delay(3000);
    
    right4();
    delay(500);
    stopMotors();
    delay(3000);
    
    right5();
    delay(500);
    stopMotors();
    delay(3000);

// Test Forward movement
    backwards1();
    delay(500);
    stopMotors();
    delay(3000);
    
    backwards2();
    delay(500);
    stopMotors();
    delay(3000);
}


#define SENSOR_1_BIT (1 << 0)
#define SENSOR_2_BIT (1 << 1)
#define SENSOR_3_BIT (1 << 2)
#define SENSOR_4_BIT (1 << 3)

#define MASK_SENSOR_1 (1 << 9)    // Sensor 1 = D2 (PORTD bit 1, shifted left 8 = bit 9)
#define MASK_SENSOR_2 (1 << 11)   // Sensor 2 = D1 (5th bit from left in allPinsValues)
#define MASK_SENSOR_3 (1 << 5)    // Sensor 3 = A2 (PORTF bit 5)
#define MASK_SENSOR_4 (1 << 1)    // Sensor 4 = A4 (PORTF bit 1)


uint8_t getAllOpponentSensorValues() {
    uint8_t values{ 0 };
    uint32_t allPinsValues{ ((uint32_t)PIND << 8) | PINF };
    //01110011       
    if (allPinsValues & MASK_SENSOR_1) values |= SENSOR_1_BIT;
    if (allPinsValues & MASK_SENSOR_2) values |= SENSOR_2_BIT;
    if (allPinsValues & MASK_SENSOR_3) values |= SENSOR_3_BIT;
    if (allPinsValues & MASK_SENSOR_4) values |= SENSOR_4_BIT;

    /*Serial.println();
    //Serial.print(values);
    for(int i{0}; i< 8; i++){
        Serial.print(bitRead(values, i));
    }
    Serial.println();*/

    return values;
}

void handleSerialOpponentSensors() {
    uint8_t values = getAllOpponentSensorValues();


    Serial.println(" ");
    Serial.print("Sensor1: ");
    Serial.print(values & SENSOR_1_BIT);
    Serial.println(" ");
    Serial.println(" ");
    Serial.print("Sensor2: ");
    Serial.print(values & SENSOR_2_BIT);
    Serial.println(" ");
    Serial.println(" ");
    Serial.print("Sensor3: "); 
    Serial.print(values & SENSOR_3_BIT);
    Serial.println(" ");
    Serial.println(" ");
    Serial.print("Sensor4: ");
    Serial.print(values & SENSOR_4_BIT);
    Serial.println(" ");

    
    // Serial.println();
    // //Serial.print(values);
    // for(int i{0}; i< 8; i++){
    //     Serial.print(bitRead(values, i));
    // }
    // Serial.println();


    //delay(500);
}

enum Pos {
    pos_0,
    pos_1,
    pos_2,
    pos_3,
    pos_4,
    pos_5,
    pos_6, // all 3 sensors saw
    pos_7, // middle and left diagonal
    pos_8, // middle and right diagonal
    pos_9,// left and left diagonal
    pos_10, // right diagonal and right
    pos_11,// 1,2,3,4 saw
    pos_12// 2,3,4,5 saw
};

volatile Pos lastPos{ pos_0 };


void updateLastPos(uint8_t values) {
    switch (values) {

    case SENSOR_2_BIT | SENSOR_3_BIT:
        lastPos = pos_6;
        Serial.println("pos___6");
        break;

    case SENSOR_1_BIT:
        lastPos = pos_1;
        Serial.println("pos___1");
        break;
    
    case SENSOR_2_BIT:
        lastPos = pos_2;
        Serial.println("pos___2");
        break;

    case SENSOR_3_BIT:
        lastPos = pos_4;
        Serial.println("pos___4");
        break;

    case SENSOR_4_BIT:
        lastPos = pos_5;
        Serial.println("pos___5");
        break;

    

    default:
        break;
    }
}

void handleSerialLastPos(){
    updateLastPos(getAllOpponentSensorValues());
    Serial.println();
    Serial.print("LastPos: ");
    Serial.print(lastPos);
    Serial.println();
}

bool handleLineDetection() {
    bool leftS = digitalRead(LeftLine);
    bool rightS = digitalRead(RightLine);
    //0 == has seen
    //1 == has NOT seen anything
    // uses bool values so !line[] means false
            
    if (leftS && !rightS) { //right sen saw
        backwards2();
        delay(250);
        left2();
        delay(250);
        return true;
    }

    if (!leftS && rightS) {// left sen saw
        backwards2();
        delay(250);
        right2();
        delay(250);
        return true;

    }

    if (!leftS && !rightS) {
        backwards2();
        delay(250);
        right2();
        delay(250);
        return true;
    }
    return false;

}

void handleSerialLineSensors() {
    bool leftS = digitalRead(LeftLine);
    bool rightS = digitalRead(RightLine);
    //0 == has seen
    //1 == has NOT seen anything
            
    Serial.println();
    Serial.print("Left:");
    Serial.print(leftS);
    Serial.println();
    Serial.print("Right:");
    Serial.print(rightS);
    Serial.println();
}


void handleLineDetectionNoBackwards() {
    bool leftS = digitalRead(LeftLine);
    bool rightS = digitalRead(RightLine);
    //0 == has seen
    //1 == has NOT seen anything
    // uses bool values so !line[] means false

    if (!leftS && rightS) { //right sen saw
        right2();
        delay(250);
    }
    if (leftS && !rightS) {// left sen saw
        left2();
        delay(250);
    }
    if (leftS && rightS) {
        stopMotors();
        delay(70);
        right2();
        delay(250);
    }

}

void handleOpponentDetection() {
    Serial.print(lastPos);
    Serial.println("pos: ");

    switch (lastPos) {
    case pos_0:
        forward3();
        break;
     case pos_1:
        left1();
        break;
    case pos_2:
        left2();
        break;
    case pos_3:
        forward2();
        break;
    case pos_4:
        right2();
        break;
    case pos_5:
        right1();
        break;
    case pos_6:
        forward1();
        break;

    case pos_7:
        left3();
        break;
    case pos_8:
        right3();
        break;

    case pos_9:
        left2();
        break;
    case pos_10:
        left2();
        break;
        
    case pos_11:
        left2();
        //if(getAllOpponentSensorValues)
        break;
    case pos_12:
        right2();

        break;
    }
   
}

void handleOpponentDetectionNoLastPos() {
    uint8_t values = getAllOpponentSensorValues();
    //Serial.print(values, BIN);
    //Serial.println(" bits");

     switch (values) {

    case SENSOR_2_BIT | SENSOR_3_BIT:
        forward1();
        break;

    case SENSOR_1_BIT:
        left1();
        break;
    
    case SENSOR_2_BIT:
        left3();
        break;

    case SENSOR_3_BIT:
        right3();
        break;

    case SENSOR_4_BIT:
        right1();
        break;

    

    default:
        break;
    }
}

void handleOpponentDetection_Flank() {

    switch (lastPos) {
    case pos_1:
        left1();
        //xmotion.Left0(flank.sideSpeed, flank.sideTime);
        sideSaw = true;
        break;
   // case pos_2:
   //     //xmotion.ArcTurn(flank.towardsSideSpeed, flank.oppositeSideSpeed, flank.diagonalTime);
   //     break;
   // case pos_3:
   //     //xmotion.Forward(flank.frontSpeed, flank.frontTime);
   //     sideSaw = true;
    //    break;
   // case pos_4:
   //     //xmotion.ArcTurn(flank.oppositeSideSpeed, flank.towardsSideSpeed, flank.diagonalTime);
   //    break;
    case pos_5:
        right1();
        //xmotion.Right0(flank.sideSpeed, flank.sideTime);
        sideSaw = true;
        break;
    case pos_6:
        forward1();
        //xmotion.Forward(flank.fullFrontSpeed, flank.fullFrontTime);
        sideSaw = true;
        break;
    case pos_0:
        forward3();
        //xmotion.Forward(flank.frontSpeed, flank.frontTime);
    }

}


bool hasBeenActiveForXTime(bool current_flag_state, unsigned long &u) {
    if (current_flag_state) {
        if (u == 0) {
            // Flag just became true
            u = millis();
        }
        
        // Check if 2 seconds (2000ms) have passed
        if (millis() - u >= 2000) {
            return true;
        }
    } else {
        // Flag is false, reset the timer
        u = 0;
    }
    
    return false;
}

bool handleCombatAndLine(){
    updateLastPos(getAllOpponentSensorValues());
    bool isCharging = false; 
    
    if (lastPos == pos_2) pos7_flag = true; else pos7_flag = false;
    if (lastPos == pos_4) pos8_flag = true; else pos8_flag = false;

    if (hasBeenActiveForXTime(pos7_flag, pos7_flag_start_timer) || 
        hasBeenActiveForXTime(pos8_flag, pos8_flag_start_timer)) {
        isCharging = true;
    } 

    Serial.print(lastPos);
    Serial.println("pos: ");

    switch (selectedStrategy){
        case normal:
            if (handleLineDetection()) return false;
            if(isCharging) {
                forward1();
            }else {
                handleOpponentDetection();
            }

            Serial.println("normal!");
            break;
        case flankS:
        Serial.println("flanks!");
            if(sideSaw){
                if (handleLineDetection()) return false;
                handleOpponentDetection();
                // Serial.println("Case flankS- sideSaw");
            }
            else{
                if (handleLineDetection()) return false;
                handleOpponentDetection_Flank();
                //  Serial.println("Case flankS- DIDN'T SAW");
            }
            break;
        case allIn:
        Serial.println("allin!");
            if (handleLineDetection()) return false;
                if (isCharging) {
                forward1(); 
            } else {
            handleOpponentDetection();
            }
            break;
        case lineTest:
        Serial.println("lineTest!");
            if (handleLineDetection()) return false;// handleLineDetectionNoBackwards should be converted to bool and then typed here
                if (isCharging) {
                forward1(); 
            } else {
            handleOpponentDetection();
            }
            break;
        case zigzag:
        Serial.println("zigzag!");
            if(handleLineDetection()) return false;
                if(checkTimer(timer1, 400)){
                    if(zigzagLeft){
                        movement.speedM1M2(7, 20 );  // Left turn
                    } else {
                        movement.speedM1M2(20, 7 );  // Right turn
                    }
                    zigzagLeft = !zigzagLeft;  // Toggle direction
            }

                if (isCharging) {
                forward1(); 
            } else {
            handleOpponentDetectionNoLastPos();
            }
            break;
        case suicide:
        Serial.println("suicide!");
            forward2();
            delay(150);
            backwardsRight();
            delay(300);
            break;
    }  

    return true;
}

void setup() {
    //xmotion.StopMotors(100);
    //xmotion.ToggleLeds(100);
    stopMotors();
    pinMode(Led1, OUTPUT);
    pinMode(RightSensor, INPUT);
    pinMode(MiddleRightSensor, INPUT);
    pinMode(MiddleLeftSensor, INPUT);
    pinMode(LeftSensor, INPUT);
    pinMode(Dip1, INPUT);
    pinMode(Dip2, INPUT);
    pinMode(Dip3, INPUT);
    pinMode(Start, INPUT);
    //pinMode(ServoPin, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
   // myServo.attach(ServoPin);
    bool dipS_V[]{ digitalRead(Dip1), digitalRead(Dip2), digitalRead(Dip3) };
    if(dipS_V[0]  && dipS_V[1] && dipS_V[2]) selectedStrategy = normal  ;// 0-0-0
    else if(!dipS_V[0] && dipS_V[1] && dipS_V[2]) selectedStrategy = flankS  ;// 1-0-0
    else if(dipS_V[0] && !dipS_V[1]  && dipS_V[2] ) selectedStrategy = allIn  ;// 0-1-0
    else if(dipS_V[0]  && dipS_V[1]  && !dipS_V[2] ) selectedStrategy = lineTest ;// 0-0-1
    else if(!dipS_V[0]  && !dipS_V[1]  && dipS_V[2] ) selectedStrategy = zigzag ;//  1-1-0
    else if(!dipS_V[0]  && dipS_V[1]  && !dipS_V[2] ) selectedStrategy = suicide ;// 1-0-1
                                                                                // 0-1-1
                                                                                //  1-1-1

    else if(dipS_V[0]  && dipS_V[1]  && dipS_V[2] ) selectedStrategy = err ; 
    Serial.println(selectedStrategy);

    if(selectedStrategy == allIn){
        speed.forward2 = 100;
        speed.forward1 = 100;
        speed.forward3 = 100;
        baseSpeed = 80;
    }

    if(selectedStrategy == zigzag){
        speed.forward2 = 15;

    }
    //pinMode(2, OUTPUT);
    Serial.begin(9600);
}
enum ModeToRun{
    normalM,
    printOpponentM,
    printLineM,
    handleLineOnlyM
};
//the M after each mode stands for Mode in order to keep unique variabels without a namespace
enum ModeToRun WhatToRun = normalM;

bool isDebugMode(){
    if(WhatToRun == printOpponentM || WhatToRun == printLineM ) return true;

    return false;
}

bool canExecute(){
    if(isDebugMode()) return true;
    return (digitalRead(Start) == HIGH);
}

void loop() {
    if(!canExecute()){
        stopMotors();
        return;
    }
    
    if(!runOnce && !isDebugMode()){
        forward3();
        delay(150);
        runOnce = true;
        timer1 = millis();
    } 

    switch (WhatToRun){
        case normalM:
            handleCombatAndLine();
            break;
        
        case printOpponentM:
            handleSerialOpponentSensors();
            handleSerialLastPos();
            delay(300);
            break;

        case printLineM:
            handleSerialLineSensors();
            delay(300);
            break;

        case handleLineOnlyM:
            handleLineDetection();
            break;
        
        default:
            handleCombatAndLine();
            break;

    }
      
}
