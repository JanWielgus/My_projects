/*
	20.04.2017r.
	Author: Jan Wielgus
*/


#include "RegulatorPID.h"

void RegulatorPIDClass::init(double _kP, double _kI, double _kD)
{
	kP = _kP;
	kI = _kI;
	kD = _kD;
}


void RegulatorPIDClass::addNewSample(double _sample)
{
	sample = _sample;
}


void RegulatorPIDClass::setSetPoint(double _setPoint)
{
	setPoint = _setPoint;
}


double RegulatorPIDClass::process()
{
	error = setPoint - sample;
	deltaTime = (millis() - lastProcess) / 1000.0;
	lastProcess = millis();
	
	//P
	P = error * kP;
	
	//I
	I = I + (error * kI) * deltaTime;
	
	//D
	D = (lastSample - sample) * kD / deltaTime;
	lastSample = sample;
	
	pid = P + I + D;
	
	return pid;
}


