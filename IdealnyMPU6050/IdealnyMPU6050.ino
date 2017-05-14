/*
* Created: 14.05.2017
* Editor: Jan Wielgus
* Ideal measurment of MPU6050 accelerometer
* using komplementary filter.
* Values almost without delay!
*/

#include <Wire.h>
#include <MPU6050.h>

#define ACCELEROMETER_SENSITIVITY 8192.0 // oryginal is 8192.0
#define GYROSCOPE_SENSITIVITY 65.536 // oryginal is 65.536
#define M_PI 3.14159265359


float pitchAcc, rollAcc, pitch, roll;
double dt, kt;

MPU6050 mpu;

void setup()
{
	Serial.begin(115200);

	Serial.println("Initialize MPU6050");

	while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
	{
		Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
		delay(500);
	}
}

void loop()
{
	//dt = (double)(micros() - kt) / 1000000; //za mało
	dt = 0.01; //zobaczyć jak wyliczyć czas!!!!
	
	Vector normAccel = mpu.readNormalizeAccel();
	Vector normGyro = mpu.readNormalizeGyro();
	
	int gx = normGyro.XAxis;
	int gy = normGyro.YAxis;
	int ax = normAccel.XAxis;
	int ay = normAccel.YAxis;
	int az = normAccel.ZAxis;

	// Integrate the gyroscope data -> int(angularSpeed) = angle
	pitch += (gx / GYROSCOPE_SENSITIVITY) * dt; // Angle around the X-axis
	roll -= (gy / GYROSCOPE_SENSITIVITY) * dt; // Angle around the Y-axis

	// Compensate for drift with accelerometer data if !bullshit
	// Sensitivity = -2 to 2 G at 16Bit -> 2G = 32768 && 0.5G = 8192
	int forceMagnitudeApprox = abs(ax) + abs(ay) + abs(az);
	if (forceMagnitudeApprox > 8192 && forceMagnitudeApprox < 32768)
	{
		// Turning around the X axis results in a vector on the Y-axis
		pitchAcc = atan2f(ay, az) * 180 / M_PI;
		pitch = pitch * 0.98 + pitchAcc * 0.02;

		// Turning around the Y axis results in a vector on the X-axis
		rollAcc = atan2f(ax, az) * 180 / M_PI;
		roll = roll * 0.98 + rollAcc * 0.02;
	}

	Serial.print(pitch);
	Serial.print("\t");
	Serial.println(roll);
	
	//kt = (double)micros();
}

