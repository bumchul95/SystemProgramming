#include <stdio.h>
#include <wiringPi.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define LED1_PIN 29 // GPIO 29
#define LED2_PIN 28 // GPIO 28

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

