/*
 * This is the implementation file that goes with Sensor.h
 * It gives control of a motor attached to DFRobotics Sensor Shield for the
 * Arduino.  The constructor needs the pin numbers for the enable pin
 * that controls direction (HIGH/LOW) and for the pwm pin that controls 
 * speed. It should work for pretty much any pwm controlled motor even with
 * other controllers.
 * author - Rob Mackie
 * date   - 10/20/2013
 */
#include "Sensor.h"
#define MAX_READING 1023

Sensor::Sensor(sensor_id_t sensor_id)
{
    analog_pin = sensor_id;
}

void Sensor::setup(void)
{
   /*
    *  nothing to do here
    */
}

void Sensor::set_mode(mode_t mode)
{
	this->mode = mode;
}

int Sensor::read(int &s1)
{
    if (DIFFERENCE_MODE == mode) {
	    return (false);
    } 
    s1 = analogRead(analog_pin);
    return (true);
}

int Sensor::read_difference(int &s1, int &s2)
{
    if (SIMPLEX_MODE == mode) {
	    return (false);
    } 
    int value = analogRead(analog_pin);
	s1 = value;
	s2 = MAX_READING - value;
}

void Sensor::calibrate(void)
{
  int current_level;
  this->read(current_level);
  avg_illumination = current_level;
}

int Sensor::get_light_level(void)
{
  return (avg_illumination);
}
