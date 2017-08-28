/*
	20.04.2017r.
	Author: Jan Wielgus
*/


#include "RegulatorPID.h"

RegulatorPIDClass PID;

#define pin 0 //analogowy pin 0 od potenc

uint16_t sygnal = 0;
uint16_t sygnalPID = 0;


void setup()
{
	Serial.begin(115200);
	PID.init(1.0, 0, 0);
	PID.setSetPoint(500);
}

void loop()
{
	sygnal = analogRead(pin);
	PID.addNewSample(sygnal);
	
	sygnalPID = PID.process();
	Serial.println(sygnalPID);
}

