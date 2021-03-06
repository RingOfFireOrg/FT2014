#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
//
#include "utility/Adafruit_PWMServoDriver.h"

int left = 0;
Adafruit_MotorShield AFMS(0x60); // default address 0x60
Adafruit_MotorShield AFMS2(0x61); // next address 0x61
// Connect two steppers with 200 steps per revolution (1.8 degree)
// to the top shield
Adafruit_StepperMotor *motor_right = AFMS.getStepper(200, 1);
Adafruit_StepperMotor *motor_left = AFMS.getStepper(200, 2);
Adafruit_StepperMotor *motor_arm = AFMS2.getStepper(200, 1);

#define STEP_TYPE INTERLEAVE
#define SPEED_LEVEL 50

void forwardstep(Adafruit_StepperMotor *m) 
{  
  m->step(10, FORWARD, STEP_TYPE);
}
void backwardstep(Adafruit_StepperMotor *m) 
{  
  m->step(10, BACKWARD, STEP_TYPE);
}

void go_forward(void)
{
  motor_right->step(5, FORWARD, STEP_TYPE);
  motor_left->step(5, FORWARD, STEP_TYPE);
  motor_right->step(5, FORWARD, STEP_TYPE);
  motor_left->step(5, FORWARD, STEP_TYPE);
}

void go_backward(void)
{
  motor_right->step(5, BACKWARD, STEP_TYPE);
  motor_left->step(5, BACKWARD, STEP_TYPE);
  motor_right->step(5, BACKWARD, STEP_TYPE);
  motor_left->step(5, BACKWARD, STEP_TYPE);
}

void go_right(void) 
{
  motor_right->step(10, FORWARD, STEP_TYPE);
}

void go_left(void) 
{
  motor_left->step(10, FORWARD, STEP_TYPE);
}

void reverse_right(void) 
{
  motor_right->step(10, BACKWARD, STEP_TYPE);
}

void reverse_left(void) 
{
  motor_left->step(10, BACKWARD, STEP_TYPE);
}

void arm_up(void)
{
  motor_arm->step(10, BACKWARD, STEP_TYPE);
}



void setup ()
{
  // open the serial port:
  Serial.begin(9600);       
  Serial.println("Robot 3 - Praise Fred");
  Serial.println("");
  AFMS.begin();
  motor_right->setSpeed(SPEED_LEVEL);
  motor_left->setSpeed(SPEED_LEVEL);
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
  case 'z':
    reverse_left();
    break;
  case 'c':  
    reverse_right();
    break;
  default:
    break;
  }
}





