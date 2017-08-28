/*
*	Created: 05.05.2017
*	Author: Jan Wielgus
	
	Kalman filter without rate (without gyro only accel)
*/

#include "FiltrKalmana.h"

FiltrKalmanaClass kal; //create new object (you can create several objects)

uint16_t value; //raw value
uint16_t kalmanValue; //value after KF

void setup()
{
	Serial.begin(115200);
	kal.init(); //init kalman filter
}

void loop()
{
	value = analogRead(0); //read raw measure
	kalmanValue = kal.update(value); //calculate
	
	Serial.print(value);
	Serial.print("\t");
	Serial.println(kalmanValue);
}
