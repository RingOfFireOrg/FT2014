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

//Constants
double wheel_base = 11;
double wheel_diameter = 2.25;

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
void go_forward(int dist){
  	stepper1.moveTo(stepper1.currentPosition()+dist);
    	stepper2.moveTo(stepper2.currentPosition()+dist);
}

void go_left(int dist){
  	stepper1.moveTo(stepper1.currentPosition()+dist);
    	stepper2.moveTo(stepper2.currentPosition()+0);
}

void go_right(int dist){
  	stepper1.moveTo(stepper1.currentPosition()+0);
    	stepper2.moveTo(stepper2.currentPosition()+dist);
}

void go_backward(int dist){
  	stepper1.moveTo(stepper1.currentPosition()-dist);
    	stepper2.moveTo(stepper2.currentPosition()-dist);
}

void reverse_left(int dist){
  	stepper1.moveTo(stepper1.currentPosition()+0);
    	stepper2.moveTo(stepper2.currentPosition()-dist);
}

void reverse_right(int dist){
  	stepper1.moveTo(stepper1.currentPosition()-dist);
    	stepper2.moveTo(stepper2.currentPosition()+0);
}

void setup ()
{
  // open the serial port:
  Serial.begin(9600);       
  Serial.println("Robot 5");
  Serial.println("");
  AFMStop.begin(); // Start the top shield
   
  stepper1.setMaxSpeed(500.0);
  stepper1.setAcceleration(500.0);
  stepper1.setSpeed(500);  
    
  stepper2.setMaxSpeed(500.0);
  stepper2.setAcceleration(500.0);
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
  else
  {
    pt_loop('q');
  }
}

void go_turn(int turn_angle)
{
  //turn_angle is degrees
  //2*pi*radius is circumference (inches / 360 degrees) ... thus 2*pi*wheel_base / 360 is inches/degree
  //2*pi*wheel_base*turnangle / 360 ... is inches
  //200 steps per wheel_diameter ... is steps/inch
  //2*pi*wheel_base*turnangle*200 / (360*wheel_diameter) is steps
  double to_move = 2*3.14159*wheel_base*turn_angle*200 / (360*wheel_diameter);
  int steps = (int) to_move;
  if (turn_angle > 0)
  {
    go_right(steps);
  }
  else if (turn_angle < 0)
  {
    go_left(steps);
  }
}

void go_autonomous(int turn1, int move1, int turn2, int move2)
{
  go_turn(turn1);
  go_forward(move1);
  go_turn(turn2);
  go_forward(move2);
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
  case 'A':
    go_autonomous(-135, 300, -90, 300);
    break;
  default:
    break;
  }

   stepper1.run();
   stepper2.run();
}





