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

#include <Servo.h>

//Adafruit_MotorShield AFMSbot(0x61); // Rightmost jumper closed
Adafruit_MotorShield AFMStop(0x60); // Default address, no jumpers

// Connect two steppers with 200 steps per revolution (1.8 degree)
// to the top shield
Adafruit_StepperMotor *myStepper1 = AFMStop.getStepper(200, 1);
Adafruit_StepperMotor *myStepper2 = AFMStop.getStepper(200, 2);

Servo servo1;
Servo servo2;

// Connect one stepper with 200 steps per revolution (1.8 degree)
// to the bottom shield
//Adafruit_StepperMotor *myStepper3 = AFMSbot.getStepper(200, 2);
// you can change these to DOUBLE or INTERLEAVE or MICROSTEP!
// wrappers for the first motor!
void forwardstep1() {  
  myStepper1->onestep(FORWARD, SINGLE);
}

void backwardstep1() {  
  myStepper1->onestep(BACKWARD, SINGLE);
}
// wrappers for the second motor!
void forwardstep2() {  
  myStepper2->onestep(FORWARD, SINGLE);
}
void backwardstep2() {  
  myStepper2->onestep(BACKWARD, SINGLE);
}
// Now we'll wrap the 3 steppers in an AccelStepper object
AccelStepper stepper1(forwardstep1, backwardstep1);
AccelStepper stepper2(forwardstep2, backwardstep2);

//Brysons code
void go_forward(void){
  	stepper1.moveTo(stepper1.currentPosition()+100);
    	stepper2.moveTo(stepper2.currentPosition()+100);
   stepper1.runSpeed();
   stepper2.runSpeed();
}

void go_left(void){
  	stepper1.moveTo(stepper1.currentPosition()+10);
    	stepper2.moveTo(stepper2.currentPosition()+0);
   stepper1.run();
   stepper2.run();
}

void go_right(void){
  	stepper1.moveTo(stepper1.currentPosition()+0);
    	stepper2.moveTo(stepper2.currentPosition()+100);
   stepper1.run();
   stepper2.run();
}

void go_backward(void){
  	stepper1.moveTo(stepper1.currentPosition()-10);
    	stepper2.moveTo(stepper2.currentPosition()-10);
   stepper1.run();
   stepper2.run();
}

void reverse_left(void){
  	stepper1.moveTo(stepper1.currentPosition()+0);
    	stepper2.moveTo(stepper2.currentPosition()-10);
   stepper1.run();
   stepper2.run();
}

void reverse_right(void){
  	stepper1.moveTo(stepper1.currentPosition()-10);
    	stepper2.moveTo(stepper2.currentPosition()+0);
   stepper1.run();
   stepper2.run();
}

void setup ()
{
  // open the serial port:
  Serial.begin(9600);       
  Serial.println("Robot 4");
  Serial.println("");
  servo1.attach(10); //servo one on left
  servo2.attach(11);
  AFMStop.begin(); // Start the top shield
   
  stepper1.setMaxSpeed(500.0);
  stepper1.setAcceleration(200.0);
  stepper1.setSpeed(500);  
    
  stepper2.setMaxSpeed(500.0);
  stepper2.setAcceleration(200.0);
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
  case 'w':
    go_forward();
    break;
  case 'a':
    go_left();
    break;
  case 'd':
    go_right();
    break;
  case 's':
    go_backward(); 
    break;
  case 'q':
    reverse_left();
    break;
  case 'e':  
    reverse_right();
    break;
    
  case '9': //Down
    servo1.write(map(0, 0, 255, 0, 180));
    servo2.write(map(180, 0, 255, 0, 180));
    break;
    
  case '0':  //Up
    servo1.write(map(115, 0, 255, 0, 180));
    servo2.write(map(65, 0, 255, 0, 180));
    break;
    
  default:
    break;
  }
}





