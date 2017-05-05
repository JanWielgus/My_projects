/*
*	Created: 05.05.2017
*	Author: Jan Wielgus
*/

#include <Wire.h>

uint8_t buf[5];
uint8_t counter = 0;

void setup() {
	Wire.begin();
	Serial.begin(115200);
}

void loop()
{
	counter = 0;
	Wire.requestFrom(8, sizeof(buf)); //request (bytes) from slave device #8

	while (Wire.available()) //Recieve bytes while available. Slave may send less than requested
	{
		buf[counter] = Wire.read(); //receive a byte
		
		//show 2/5 on serial to check if working (you can use all parts of array)
		Serial.print(buf[0]);
		Serial.print("\t");
		Serial.println(buf[3]);
		
		counter++;
	}

	delay(500); //request every 500ms
}