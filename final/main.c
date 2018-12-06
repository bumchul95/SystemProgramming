#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <fcntl.h>

#include "dht11temp.h"
#include "led.h"
#include "gravity.h"

#define TOUCH_DEV_PATH "/dev/touch_dev"
#define BUZZER_DEV_PATH "/dev/buzzer_dev"

int main(void){

	int touch_state;
	float temp_value;
	float gyro_value;
	
        int touch_fd = open(TOUCH_DEV_PATH, O_RDWR);
	int buzzer_fd = open(BUZZER_DEV_PATH, O_RDWR);

	if(touch_fd == -1 || buzzer_fd == -1) // error exist
		return -1;

	while(1) {
		read(touch_fd, &touch_state, sizeof(touch_state));
		printf("touch_state is %d.\n", touch_state);

		// if bed is touched
		if(touch_state){
	
		  //temperature estimate
		  temp_value = read_dht11_dat();
		  gyro_value = gyro();
                  write(buzzer_fd, "on", 2);

		  printf("gyro_value : %.2f\n", gyro_value);
					
		  if(temp_value){ // if temp exists
			if(temp_value > 20.0){ // high
				printf("temp is %.2f\n",temp_value);
				LED1_ON();
			}
			else{  //low
				printf("temp is %.2f\n",temp_value);
				LED2_ON();
		        }
		  }
		}
		// if bed is not touched
		else {
			LED2_ON();
		}
	}

	return 0;
}


