#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>

#define SERVO 5

int main()
{
	int nBright;

	if(wiringPiSetup() == -1)
		return 1;

	softPwmCreate( SERVO, 0, 200);

	while(1) {
		softPwmWrite(SERVO, 100);
		usleep(10000000);
	}

	
	return 0;
}
