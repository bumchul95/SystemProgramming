#ifndef __LED_H__
#define __LED_H__

#include <stdio.h>
#include <wiringPi.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

#define LED1_PIN 29 // GPIO 29
#define LED2_PIN 28 // GPIO 28

void LED1_ON();
void LED2_ON();
void INT_handler(int);
void init();

#endif
