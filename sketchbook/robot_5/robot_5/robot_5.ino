// Shows how to run three Steppers at once with varying speeds
//
// Requires the Adafruit_Motorshield v2 library 
//   https://github.com/adafruit/Adafruit_Motor_Shield_V2_Library
// And AccelStepper with AFMotor support 
//   https://github.com/adafruit/AccelStepper

// This tutorial is for Adafruit Motorshield v2 only!
// Will not work with v1 shields

#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"

//Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

// Connect two steppers with 200 steps per revolution (1.8 degree)
// to the top shield
Adafruit_StepperMotor *myStepper1 = AFMStop.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(200, 2);

// Connect one stepper with 200 steps per revolution (1.8 degree)
// to the bottom shield
//Adafruit_StepperMotor *myStepper3 = AFMSbot.getStepper(200, 2);
// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {  
  myStepper1->onestep(FORWARD, DOUBLE);
}

void backwardstep1() {  
  myStepper1->onestep(BACKWARD, DOUBLE);
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
  	stepper1.moveTo(stepper1.currentPosition()+300);
    	stepper2.moveTo(stepper2.currentPosition()+300);
//   stepper1.runSpeed();
//   stepper2.runSpeed();
}

void go_left(void){
  	stepper1.moveTo(stepper1.currentPosition()+10);
    	stepper2.moveTo(stepper2.currentPosition()+0);
}

void go_right(void){
  	stepper1.moveTo(stepper1.currentPosition()+0);
    	stepper2.moveTo(stepper2.currentPosition()+100);
}

void go_backward(void){
  	stepper1.moveTo(stepper1.currentPosition()-300);
    	stepper2.moveTo(stepper2.currentPosition()-300);
//  	stepper1.moveTo(stepper1.currentPosition()-10);
//    	stepper2.moveTo(stepper2.currentPosition()-10);
}

void reverse_left(void){
  	stepper1.moveTo(stepper1.currentPosition()+0);
    	stepper2.moveTo(stepper2.currentPosition()-10);
}

void reverse_right(void){
  	stepper1.moveTo(stepper1.currentPosition()-10);
    	stepper2.moveTo(stepper2.currentPosition()+0);
}

void setup ()
{
  // open the serial port:
  Serial.begin(9600);       
  Serial.println("Robot 5");
  Serial.println("");
  AFMStop.begin(); // Start the top shield
   
  stepper1.setMaxSpeed(1500.0);
  stepper1.setAcceleration(200.0);
  stepper1.setSpeed(1500);  
    
  stepper2.setMaxSpeed(1500.0);
  stepper2.setAcceleration(200.0);
  stepper2.setSpeed(1500); 
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
  else
  {
    pt_loop('q');
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
  default:
    break;
  }

   stepper1.run();
   stepper2.run();
}





