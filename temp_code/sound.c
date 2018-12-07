#include <stdio.h>
#include <wiringPi.h>

#define SOUND 21

int sound(void){
	wiringPiSetupGpio();
	pinMode(SOUND, INPUT);

	while(1){
		if(digitalRead(SOUND)==LOW){
			printf("Sound detected!");
			delay(100);
			printf("\n");
		}else{
			printf("No sound");
			delay(100);
			printf("\n");
		}
	
	}
	return 0;
}
