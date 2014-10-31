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

#ifndef __MOTOR__
#define __MOTOR__

#include "Arduino.h"

class MotorRobotBase {
  public:
    enum motor_id_t {MOTOR_1, MOTOR_2};
    MotorRobotBase(motor_id_t motor_id);

    void setup(void);
    void forward(unsigned char speed);
    void reverse(unsigned char speed);
    void stop(void);
    
  protected:
    static int const FORWARD = HIGH;
    static int const REVERSE = LOW;
    
  private:
    int pin_e; // speed pin pwm
    int pin_1;
    int pin_2;
    void set_forward();
    void set_reverse();
    void set_stop();
};

#endif //__MOTOR__

