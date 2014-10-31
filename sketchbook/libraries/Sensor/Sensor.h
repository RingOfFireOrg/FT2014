/*
 * This is the implementation file that goes with Sensor.h
 * It gives control of a photo resistor attached to DFRobotics Sensor Shield for the
 * Arduino.  The constructor needs the pin numbers for the enable pin
 * that controls direction (HIGH/LOW) and for the pwm pin that controls 
 * speed. It should work for pretty much any pwm controlled motor even with
 * other controllers.
 * author - Rob Mackie
 * date   - 10/20/2013
 */

#ifndef __SENSOR__
#define __SENSOR__

#include "Arduino.h"

class Sensor {
  public:
    enum sensor_id_t {SENSOR_0, SENSOR_1, SENSOR_2, SENSOR_3, SENSOR_4, SENSOR_5};
    enum mode_t {SIMPLEX_MODE, DIFFERENCE_MODE};

    Sensor(sensor_id_t sensor_id);

    void setup(void);
    void set_mode(mode_t mode);
    int read(int &s1);
    int read_difference(int &s1, int &s2);
    void calibrate();
    int get_light_level(void);
    
  private:
    int analog_pin;
    mode_t mode;
    int avg_illumination;
};

#endif //__SENSOR__
