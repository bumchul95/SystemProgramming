
#include "led.h"

void init(){
	digitalWrite(LED1_PIN, LOW);
	digitalWrite(LED2_PIN, LOW);
}

void INT_handler(int sig){
	init();
	exit(0);
}

void LED1_ON(){
	wiringPiSetup();
	signal(SIGINT, INT_handler);
	
	pinMode(LED1_PIN, OUTPUT);	
	pinMode(LED2_PIN, OUTPUT);
	
	digitalWrite(LED1_PIN, HIGH);
	digitalWrite(LED2_PIN, LOW);
}

void LED2_ON(){
	wiringPiSetup();
	signal(SIGINT, INT_handler);

	pinMode(LED1_PIN, OUTPUT);	
	pinMode(LED2_PIN, OUTPUT);
	
	digitalWrite(LED1_PIN, LOW);
	digitalWrite(LED2_PIN, HIGH);
}

