#include <stdio.h>
#include <wiringPi.h>

#define TOUCH 1 // GPIO 24

int main(void)
{
	wiringPiSetup();
	pinMode(TOUCH, INPUT);

	while(1){
		if(digitalRead(TOUCH) == 1)
			printf("TOUCHED\n");
		else
			printf("NOT\n");
		delay(1000);
	}

	return 0;
}
