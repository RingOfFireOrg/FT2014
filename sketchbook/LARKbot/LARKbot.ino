// Arduino PWM Speed Control：
// Pin definitions for PWM speed control using 
// DFRobot Arduino Compatible Motor Shield (2A):

//#define BOT_2011
#ifdef BOT_2011
#include "MotorRobotBase.h"
#define Motor MotorRobotBase
#else
#include "Motor.h" 
#endif

#include "Sensor.h"

#define FULL_SPEED 70
#define SLOW_SPEED  25
void go_right(Motor &m1, Motor &m2) 
{
  m1.reverse(SLOW_SPEED);
  m2.reverse(FULL_SPEED); 
}

void go_left(Motor &m1, Motor &m2) 
{
  m1.reverse(FULL_SPEED);
  m2.reverse(SLOW_SPEED);
}
void go_straight(Motor &m1, Motor &m2) 
{
  m1.reverse(FULL_SPEED);
  m2.reverse(FULL_SPEED);
}

void twist_right(Motor &m1, Motor &m2) 
{
  m1.reverse(FULL_SPEED);
  m2.forward(FULL_SPEED);
}

void twist_left(Motor &m1, Motor &m2) 
{
  m1.forward(FULL_SPEED);
  m2.reverse(FULL_SPEED);
}

void go_back(Motor &m1, Motor &m2) 
{
  m1.forward(FULL_SPEED);
  m2.forward(FULL_SPEED);
}

void go_back_left(Motor &m1, Motor &m2) 
{
  m1.forward(FULL_SPEED);
  m2.reverse(SLOW_SPEED);
}

void go_back_right(Motor &m1, Motor &m2) 
{
  m1.forward(SLOW_SPEED);
  m2.forward(FULL_SPEED);
}

Motor right_motor(Motor::MOTOR_1);
Motor left_motor(Motor::MOTOR_2);
Sensor light(Sensor::SENSOR_0);
Sensor on_off(Sensor::SENSOR_1);

void setup () 
{ 
  Serial.begin(9600);

  right_motor.setup();
  left_motor.setup();
  light.setup();
  light.set_mode(Sensor::SIMPLEX_MODE);
  light.calibrate();
  on_off.setup();
  on_off.set_mode(Sensor::SIMPLEX_MODE);
  on_off.calibrate();  
} 

#define SENSE 50
void loop () 
{
  char light_str[255];

  int light_level;
  int motor_state;
  
  on_off.read(motor_state);
  motor_state = 0;
  light.read(light_level);
  if (motor_state < 512) {
    if (light_level < 1018) {
      go_right(right_motor, left_motor);      
    } 
    else {
      go_left(right_motor, left_motor);     
    }
  }
  delay(50);
//  Serial.write(light_level);
  
  if (light_level > 1000) {  
   Serial.write("1000\n");    
   } else  if (light_level > 900) {  
   Serial.write("900\n");    
   } else  if (light_level > 800) {  
   Serial.write("800\n");    
   } else  if (light_level > 700) {  
   Serial.write("700\n");    
   }  else  if (light_level > 600) {  
   Serial.write("600\n");    
   }  else  if (light_level > 500) {  
   Serial.write("500\n");    
   }  else  if (light_level > 400) {  
   Serial.write("400\n");    
   }  else  if (light_level > 300) {  
   Serial.write("300\n");    
   }  else  if (light_level > 200) {  
   Serial.write("200\n");    
   }  else  if (light_level > 100) {  
   Serial.write("100\n");    
   }   else  { 
   Serial.write("00\n");    
   }
   
}







