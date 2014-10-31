/*
 * This is the implementation file that goes with MotorRobotBase.h
 * It gives control of a motor attached to DFRobotics MotorRobotBase Shield for the
 * Arduino.  The constructor needs the pin numbers for the enable pin
 * that controls direction (HIGH/LOW) and for the pwm pin that controls 
 * speed. It should work for pretty much any pwm controlled motor even with
 * other controllers.
 * author - Rob Mackie
 * date   - 10/20/2013
 */
#include "MotorRobotBase.h"

// MOTOR_1
int I1 = 7;  
int I2 = 8;                      
int EA = 9; 

// MOTOR_2
int I3 = 4;  
int I4 = 5;                      
int EB = 6;

//        free  forward reverse brake
// pin_1   0       1       0      1
// pin_2   0       0       1      1
// pin_e   pwm 0 .. 255 where 255 is full on.


MotorRobotBase::MotorRobotBase(motor_id_t motor_id)
{
  if (MOTOR_1 == motor_id) {
    pin_1 = I1;
    pin_2 = I2;
    pin_e = EA; // speed pin pwm
  } else {
    pin_1 = I3;
    pin_2 = I4;
    pin_e = EB; // speed pin pwm
  }
}

void MotorRobotBase::setup(void)
{
  pinMode(pin_1, OUTPUT);
  pinMode(pin_2, OUTPUT);
  pinMode(pin_e, OUTPUT);
}

void MotorRobotBase::set_forward()
{
	digitalWrite(pin_1, HIGH);
	digitalWrite(pin_2, LOW);
}

void MotorRobotBase::set_reverse()
{
	digitalWrite(pin_1, LOW);
	digitalWrite(pin_2, HIGH);
}

void MotorRobotBase::set_stop()
{
	digitalWrite(pin_1, LOW);
	digitalWrite(pin_2, LOW);
}

void MotorRobotBase::forward(unsigned char speed)
{
    set_forward();
    analogWrite(pin_e, speed);
}

void MotorRobotBase::reverse(unsigned char speed)
{
    set_reverse();
    analogWrite(pin_e, speed);
}

void MotorRobotBase::stop(void)
{
    set_stop();
    analogWrite(pin_e, 0);
}

