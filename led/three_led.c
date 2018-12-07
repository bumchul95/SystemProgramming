#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#define PIN_B 1 //GPIO18
#define PIN_R 0 //GPIO17
void init();
void INT_handler(int sig){
	init();
	exit(0);
}

void init(){
	softPwmWrite(PIN_B, 0);
}

int main(void){
	int i, j;
	wiringPiSetup();

	pinMode(PIN_B, OUTPUT);
	//pinMode(PIN_R, OUTPUT);
	softPwmCreate(PIN_B, 0, 255);
	while(1){
		softPwmWrite(PIN_B, 255);
	}
	//softPwmCreate(PIN_R, 0, 255);
	/*
	for(i = 0; i <= 250; i=i+30){
		softPwmWrite(PIN_B, 255 - i);
		softPwmWrite(PIN_R, 255 - i);
		delay(500);
	}

	softPwmWrite(PIN_B, 0);
	softPwmWrite(PIN_R, 0);
	delay(500);
	*/
	return 0;
}
