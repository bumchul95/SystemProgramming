#include <stdio.h>
#include <wiringPi.h>

#define PIR 4

int touch(void){
	if(wiringPiSetup() == -1)
		return -1;

	pinMode(PIR,INPUT);
	
	if(digitalRead(PIR) == 0){
//		printf("not detection\n");
		delay(1000);
		return digitalRead(PIR);
	}else{
//		printf("detection\n");
		delay(1000);
		return digitalRead(PIR);
	}
}

