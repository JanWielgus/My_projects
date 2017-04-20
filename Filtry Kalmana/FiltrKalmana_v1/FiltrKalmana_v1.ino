#include "FiltrKalmana.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"


MPU6050 accelgyro;

FiltrKalmanaClass kalmanXm;
FiltrKalmanaClass kalmanYm;

float accPitch = 0;
float accRoll = 0;

float kalPitch = 0;
float kalRoll = 0;

int16_t ax, ay, az;
int16_t gx, gy, gz;

void setup()
{
	Serial.begin(115200);

	accelgyro.initialize();
	
	kalmanXm.init(0.001, 0.003, 0.03);
	kalmanYm.init(0.001, 0.003, 0.03);
}

void loop()
{
	accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
	
	accPitch = ay;
	accRoll = ax;

	//kalPitch = kalmanYm.update(accPitch, gy);
	//kalRoll = kalmanXm.update(accRoll, gx);
	kalPitch = kalmanYm.update(accPitch, 0);
	kalRoll = kalmanXm.update(accRoll, 0);
	
	
	Serial.print(int(kalPitch));
	Serial.print("\t");
	Serial.print(ay);
	Serial.print("\t");
	Serial.print(int(kalRoll));
	Serial.print("\t");
	Serial.println(ax);
}

