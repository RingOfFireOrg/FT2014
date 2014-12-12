
#include <AccelStepper.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_PWMServoDriver.h"
#include <Servo.h> 

Servo servo1;
Servo servo2;
int asNumber;
int location;
Adafruit_MotorShield DefaultShield(0x60); // Default address, no jumpers

void setup() 
{ 
  // open the serial port:
  Serial.begin(9600);
  Serial.println("Servo Test");
  Serial.println("");
  DefaultShield.begin(); // Start the top shield
  servo1.attach(9);
  servo2.attach(10);
  asNumber = 1;
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

Servo get_active_servo(int num)
{
  switch (num) {
    case 1:
      return servo1;
    case 2:
      return servo2;
    default:
      Serial.print("Invalid Servo: ");
      Serial.print(num);
      Serial.println();
      return servo1;
  }  
}

/*
  PyroTech Loop - this is where you code goes. You will receive 
  one character "c" at a time, each time a key stroke is received 
  from the keyboard drivers station.  You can choose to have your   code do whatever you want when that character arrives.
*/
void pt_loop(char c)
{
  if (set_location(c))
  {
    Serial.print("Moving Servo ");
    Serial.print(asNumber);
    Serial.print(" to ");
    Serial.println(location);    
    get_active_servo(asNumber).write(location);
  }
}

boolean set_location(char c)
{
  int oldloc = location;
  if ((int) c != 113)
  {
    Serial.print("Input was: ");
    Serial.println((int)c);
  }
  int destination = (int)c - 48;
  if ((destination >= 0) && (destination <= 9))
  {
    location = destination * 10;
  }
  else
  {
    switch (c) {
    case '!':
      location = 110;
      break;
    case '@':
      location = 120;
      break;
    case '#':
      location = 130;
      break;
    case '$':
      location = 140;
      break;
    case '%':
      location = 150;
      break;
    case '^':
      location = 160;
      break;
    case '&':
      location = 170;
      break;
    case '*':
      location = 180;
      break;
    case '+':
      location++;
      break;
    case '-':
      location--;
      break;
    case '<':
      asNumber = 1;
      Serial.println("Using Servo 1");
      location = 0;
      break;
    case '>':
      asNumber = 2;
      Serial.println("Using Servo 2");
      location = 0;
      break;
    default:
      break;
    }
  }
  return (oldloc != location);
}

