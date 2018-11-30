#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define PIN 1

int main()
{
	if(wiringPiSetup() == -1)
		return -1;

	softPwmCreate(PIN, 0, 200);
	
	while(1){
	softPwmWrite(PIN, 5);
	delay(300);
	}
	return 0;
}
