#include <stdio.h>
#include <wiringPi.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define PIN 1 // GPIO 18

void init(){
	digitalWrite(PIN, LOW);
}

void INT_handler(int sig){
	init();
	exit(0);
}

void high(){
	wiringPiSetup();
	signal(SIGINT, INT_handler);
	pinMode(PIN, OUTPUT);	

	digitalWrite(PIN, HIGH);
//	usleep(1000*500);
}

void low(){
	wiringPiSetup();
	signal(SIGINT, INT_handler);
	pinMode(PIN, OUTPUT);	

	digitalWrite(PIN, LOW);
//	usleep(1000*500);
}

