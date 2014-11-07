/*
 * This is the implementation file that goes with Motor.h
 * It gives control of a motor attached to DFRobotics Motor Shield for the
 * Arduino.  The constructor needs the pin numbers for the enable pin
 * that controls direction (HIGH/LOW) and for the pwm pin that controls 
 * speed. It should work for pretty much any pwm controlled motor even with
 * other controllers.
 * author - Rob Mackie
 * date   - 10/20/2013
 */
#include "Motor.h"

// Motor 1
int E1 = 5;  
int M1 = 4; 

// Motor 2
int E2 = 6;                      
int M2 = 7;

Motor::Motor(int e, int m)
{
    speed_pin = e;
    direction_pin = m;
}

Motor::Motor(motor_id_t motor_id)
{
  if (MOTOR_1 == motor_id) {
    speed_pin = E1; 
    direction_pin = M1; 
  } else {
    speed_pin = E2; 
    direction_pin = M2;
  }
}

void Motor::setup(void)
{
  pinMode(direction_pin, OUTPUT);
}

void Motor::forward(unsigned char speed)
{
    digitalWrite(direction_pin, FORWARD);
    analogWrite(speed_pin, speed);
}

void Motor::reverse(unsigned char speed)
{
    digitalWrite(direction_pin, REVERSE);
    analogWrite(speed_pin, speed);
}

void Motor::stop(void)
{
    digitalWrite(direction_pin, FORWARD);
    analogWrite(speed_pin, 0);
}

