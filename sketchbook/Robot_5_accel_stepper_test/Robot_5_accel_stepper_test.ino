
#include <AccelStepper.h>

// Define some steppers and the pins the will use
AccelStepper stepper1(AccelStepper::FULL4WIRE, 0, 1, 2, 3); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper2(AccelStepper::FULL4WIRE, 4, 5, 6, 7);
AccelStepper stepper3(AccelStepper::FULL4WIRE, 8, 9, 10, 11);
AccelStepper stepper4(AccelStepper::FULL4WIRE, 12, 13, 14, 15);

void setup()
{  
    stepper1.setMaxSpeed(1000.0);
    stepper1.setAcceleration(150.0);
    stepper1.moveTo(1500);
    delay(0);   
    stepper2.setMaxSpeed(1000.0);
    stepper2.setAcceleration(145.0);
    stepper2.moveTo(1500);
    delay(0);   
    stepper3.setMaxSpeed(1000.0);
    stepper3.setAcceleration(140.0);
    stepper3.moveTo(1500);
    delay(0);   
    stepper4.setMaxSpeed(1000.0);
    stepper4.setAcceleration(135.0);
    stepper4.moveTo(1500); 
}

void loop()
{
    // Change direction at the limits
    
if (stepper1.distanceToGo() == 0)
   stepper1.moveTo(-stepper1.currentPosition());
delay(0);  
if (stepper2.distanceToGo() == 0)
   stepper2.moveTo(-stepper2.currentPosition());
delay(0);  
if (stepper3.distanceToGo() == 0)
   stepper3.moveTo(-stepper3.currentPosition());
delay(0);  
if (stepper4.distanceToGo() == 0)
   stepper4.moveTo(-stepper4.currentPosition());
    stepper1.run();
    stepper2.run();
    stepper3.run();
    stepper4.run();
}

