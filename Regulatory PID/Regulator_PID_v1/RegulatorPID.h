/*
	20.04.2017r.
	Author: Jan Wielgus
*/


#ifndef _REGULATORPID_h
#define _REGULATORPID_h


class RegulatorPIDClass
{
 public:
	double error;
	double sample;
	double lastSample;
	double kP, kI, kD;
	double P, I, D;
	double pid;
	
	double setPoint;
	float deltaTime;
	long lastProcess;
	
 public:
	void init(double _kP, double _kI, double _kD);
	void addNewSample(double _sample);
	void setSetPoint(double _setPoint);
	double process();
};

#endif

