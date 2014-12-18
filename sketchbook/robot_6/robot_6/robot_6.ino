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
#include <Servo.h> 

Servo myservo;  // create servo object to control a servo 
// a maximum of eight servo objects can be created 

int pos = 0;    // variable to store the servo position 

int left = 0;


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
AccelStepper stepper1(&forwardstep1, &backwardstep1);
AccelStepper stepper2(&forwardstep2, &backwardstep2);

//Brysons code
void go_forward(void){
  Serial.println("forward");
  	stepper1.moveTo(stepper1.currentPosition()+1000);
    	stepper2.moveTo(stepper2.currentPosition()+1000);
   stepper1.run();
   stepper2.run();
}
void go_backward(void){
  Serial.println("backward");
  	stepper1.moveTo(stepper1.currentPosition()-100);
    	stepper2.moveTo(stepper2.currentPosition()-100);
   stepper1.run();
   stepper2.run();
}
void go_left(void){
  	stepper1.moveTo(stepper1.currentPosition()+100);
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
void out_dump (void)
{ 
  for(pos = 45; pos>=1; pos-=1)     // goes from 180 degrees to 0 degrees 
  {                                
    myservo.write(pos);
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
}
void setup ()
{
  // open the serial port:
  Serial.begin(9600);       
  Serial.println("Robot 6 v2.0");
  Serial.println("");
  AFMStop.begin(); // Start the top shield
  stepper1.setMaxSpeed(500.0);
  stepper1.setAcceleration(200.0);
  stepper1.setSpeed(500);  
    
  stepper2.setMaxSpeed(500.0);
  stepper2.setAcceleration(200.0);
  stepper2.setSpeed(500); 
  myservo.attach(9);
   myservo.write(90);
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
  from the keyboard drivers station.  You can choose to oave your 
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
  case 'z':
    reverse_left();
    break;
  case 'c':  
    reverse_right();
    break;
  case 'o':
    out_dump();
    break;
  default:
    break;
  }
}





