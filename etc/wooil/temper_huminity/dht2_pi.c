#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_TIMINGS 85
#define DHT_PIN 7

int data[5] = {0, 0, 0, 0, 0 };

void read_dht_data()
{
	uint8_t laststate = HIGH;
	uint8_t counter = 0;
	uint8_t j = 0, i;

	data[0] = data[1] = data[2] = data[3] = data[4] = 0;

	pinMode( DHT_PIN, OUTPUT );
	digitalWrite( DHT_PIN, LOW );
	delay(18);

	pinMode( DHT_PIN, INPUT );

	for ( i = 0; i < MAX_TIMINGS; i++ )
	{
		counter  = 0;
		while( digitalRead(DHT_PIN) == laststate )
		{
			counter++;
			delayMicroseconds(1);

			if(counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead(DHT_PIN);

		if(counter == 255 )
			break;

		if( (i>=4) && (i % 2 == 0) )
		{
			data[j / 8] <<= 1;
			if( counter > 50)
				data[j / 8] |= 1;
			j++;
		}
	}

	if( (j >= 40) && (data[4] == ( (data[0] + data [1] + data[2] + data[3]) & 0xFF)))
	{
		float h = (float)((data[0] << 8) + data[1]) / 10;
		if(h > 100)
		{
			h = data[0];
		}
		float c = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;

		if(c > 125)
		{
			c = data[2];
		}
		if( data[2] & 0x80 )
		{
			c = -c;
		}
		float f = c * 1.8f + 32;
		printf("Humidity = %.1f %% Temperature = %.1f *C ( %.1f * F)\n", h, c, f);
	}
	else
	{
		printf("Data not good, skip\n");
	float h = (float)((data[0] << 8) + data[1]) / 10;
		if(h > 100)
		{
			h = data[0];
		}
		float c = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;

		if(c > 125)
		{
			c = data[2];
		}
		if( data[2] & 0x80 )
		{
			c = -c;
		}
		float f = c * 1.8f + 32;
		printf("Humidity = %.1f %% Temperature = %.1f *C ( %.1f * F)\n", h, c, f);

	}
}

int main(void)
{
	printf("Raspberry Pi DHT11/DHT22 temperature/humidity test\n");

	if(wiringPiSetup() == -1)
	{
		exit(1);
	}

	while(1)
	{
		read_dht_data();
		delay(2000);
	}

	return 0;
}

