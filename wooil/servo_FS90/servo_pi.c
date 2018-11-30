#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>

#define SERVO 5

int main()
{
	char str;

	if(wiringPiSetup() == -1)
		return 1;

	softPwmCreate( SERVO, 0, 200);

	while(1)
	{
		fputs("select r, l, q : ", stdout);
		scanf("%c", &str);

		getchar();

		if(str == 'r')
		{
			softPwmWrite(SERVO, 24);
			usleep(1000000);
			softPwmWrite(SERVO, 0);
		}
		else if(str == 'l')
		{
			softPwmWrite(SERVO, 5);
			usleep(1000000);
			softPwmWrite(SERVO, 0);
		}
		else if(str == 'q') return 0;
	
	}
	return 0;
}
