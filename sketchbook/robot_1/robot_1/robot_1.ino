#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

//Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

Adafruit_StepperMotor *myStepper1 = AFMStop.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(200, 2);

boolean flip = false;
boolean state1 = true, firstWiggle = true;
long lastSwitch, switchTime = 2000;

#define STEP_TYPE SINGLE

void forwardstep1() {  
  myStepper1->onestep(FORWARD, SINGLE);
}
void backwardstep1() {  
  myStepper1->onestep(BACKWARD, SINGLE);
}
// wrappers for the second motor!
void forwardstep2() {  
  myStepper2->onestep(FORWARD, DOUBLE);
}
void backwardstep2() {  
  myStepper2->onestep(BACKWARD, DOUBLE);
}
// Now we'll wrap the 3 steppers in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);
//Brysons code
void go_forward(void){
  moveWheels(40,40);
}

void go_left(void){
  moveWheels(0,40);
}

void go_right(void){
  moveWheels(40,0);
}

void go_backward(void){
  moveWheels(-40,-40);
}

void reverse_left(void){
  moveWheels(-40,0);
}

void reverse_right(void){
  moveWheels(0,-40);
}

void moveWheels(int wheel1, int wheel2) {
  int lWheel, rWheel;
  
  if(flip) {
    lWheel = wheel2;
    rWheel = wheel1;
  } else {
    lWheel = wheel1;
    rWheel = wheel2;
  }
  
  stepper1.move(lWheel);
  stepper2.move(rWheel);
  
  //while (stepper1.distanceToGo() != 0 && stepper2.distanceToGo() != 0) {
    stepper1.run();
    stepper2.run();
  //}
}

void wiggle() {
  if(firstWiggle) {
    lastSwitch = millis();
    firstWiggle = false;
  }
    
  if(abs(millis() - lastSwitch) > switchTime) {
    lastSwitch = millis();
    state1 = !state1;
  }  
  
  if(state1) {
    moveWheels(20,-20);
  } else {
    moveWheels(-20,20);
  }
}

void setup ()
{
  // open the serial port:
  Serial.begin(9600);       
  Serial.println("Robot 5");
  Serial.println("");
  AFMStop.begin(); // Start the top shield
   
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(100.0);
    
  stepper2.setMaxSpeed(1000.0);
  stepper2.setAcceleration(100.0);
  
  stepper1.setSpeed(500);
  stepper2.setSpeed(500);
}

void loop ()
{
  // check for incoming serial data:
  if (Serial.available() > 0) {
    // read incoming serial data:
    char inChar = Serial.read();
    pt_loop(inChar);
    Serial.println("ok");
   
  }
}

/*
  PyroTech Loop - this is where you code goes. You will receive 
  one character "c" at a time, each time a key stroke is received 
  from the keyboard drivers station.  You can choose to have your 
  code do whatever you want when that character arrives.
*/
void pt_loop(char c)
{
  Serial.println(c);

  switch (c) {
  case 'e':
    go_forward();
    break;
  case 's':
    go_left();
    break;
  case 'f':
    go_right();
    break;
  case 'd':
    go_backward(); 
    break;
  case 'x':
    reverse_left();
    break;
  case 'v':  
    reverse_right();
    break;
  case 'z':
    wiggle();
    break;
  default:
    break;
  }
}





