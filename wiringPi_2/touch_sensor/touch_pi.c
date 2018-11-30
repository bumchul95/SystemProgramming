#include <stdio.h>
#include <wiringPi.h>

#define PIR 4

int main(void)
{
	if(wiringPiSetup() == -1)
		return -1;

	pinMode(PIR, INPUT);

	for(;;)
	{
		if(digitalRead(PIR) == 0)
		{
			printf("Not Detected\n");
			delay(1000);
		}
		else
		{
			printf("Detection\n");
			delay(1000);
		}
	}

	return 0;

}

