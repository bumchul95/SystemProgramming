#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define PIN 1
int motor(){
	if(wiringPiSetup() == -1)
		return -1;
	softPwmCreate(PIN, 0, 200);
	
	softPwmWrite(PIN, 5);
	delay(50);
	

	return 0;

}
