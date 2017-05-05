/*
*	Created: 05.05.2017
*	Author: Jan Wielgus
*/

#include <Wire.h>

uint8_t buf[5];

void setup() {
	Wire.begin(8); //set device adress on 8
	Wire.onRequest(requestEvent); //this function start when master request
	
	//set array variables
	for (int q=0; q < 5; q++)
	{
		buf[q] = q + 2;
	}
}

void loop()
{
	delay(100); //do nothing (onRequest function is working)
}



void requestEvent()
{
	Wire.write(buf, sizeof(buf)); //on master's request send array
	
	//increment all array variables (there uou can set your own values instead of this part)
	for (int q=0; q < 5; q++)
	{
		buf[q]++;
	}
}
