#ifndef __DHT11TEMP_H__
#define __DHT11TEMP_H__

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAXTIMINGS 85
#define DHTPIN 7

float read_dht11_dat();

#endif
