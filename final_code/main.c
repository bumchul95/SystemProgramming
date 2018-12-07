#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#include "dht11temp.h"
#include "led.h"
#include "gravity.h"
#include "sender.h"

#define BED_TOUCH_DEV_PATH "/dev/bed_touch_dev"
#define PIL_TOUCH_DEV_PATH "/dev/pil_touch_dev"
#define BUZZER_DEV_PATH "/dev/buzzer_dev"

pthread_t thread;

int touch_flag = 0;
int sleep_flag = 0;
int wakeup_flag = 0;
int window_flag = 1;

void *gyro_count(void *unuse){

	float gyro_list[5] = { 0 };

	for(int i = 0; i < 5; i++){
		sleep(1);
		
		gyro_list[i] = gyro();
		printf("gyro_list[i] : %.3f\n", gyro_list[i]);

		if(i != 0){
			float gyro_dist = gyro_list[i] - gyro_list[i-1];

			if(gyro_dist >= -0.2 && gyro_dist <= 0.2)
				continue;
			else{
				sleep_flag = 0;
				pthread_exit((void *)sleep_flag);
			}
		}
	}

	sleep_flag = 1;
	pthread_exit((void *)sleep_flag);
}

int main(void){

	int bedtouch_state;
	int piltouch_state;
	float temp_value;
	float gyro_value;
	
        int bedtouch_fd = open(BED_TOUCH_DEV_PATH, O_RDWR);
	int piltouch_fd = open(PIL_TOUCH_DEV_PATH, O_RDWR);
	//int buzzer_fd = open(BUZZER_DEV_PATH, O_RDWR);
	
	int gyro_thr_id;

	if(bedtouch_fd == -1 || piltouch_fd == -1){	// error exist
		return -1;
	}
	
	while(1) {
		read(bedtouch_fd, &bedtouch_state, sizeof(bedtouch_state));
		read(piltouch_fd, &piltouch_state, sizeof(piltouch_state));
		printf("bed/pil touch_state is %d %d.\n", bedtouch_state, piltouch_state);

		// if bed is touched
		if(bedtouch_state && piltouch_state){
		 
		  if(!sleep_flag){
		    printf("gyro_thread start!\n");
		    gyro_thr_id = pthread_create(&thread, NULL, gyro_count, 0);
		  }

                  //write(buzzer_fd, "on", 2);
			
  		  if(sleep_flag){
			printf("sleep mode start !\n");
			
			if(window_flag){
			  send_from_server("down");
			  window_flag--;
			}
			
	 		//temperature estimate		  
			temp_value = read_dht11_dat();
		  	
			if(temp_value){ // if temp exists
				if(temp_value > 23.0){ // temperature is high
					printf("temp is %.2f\n",temp_value);
					LED1_ON();
				}
				else{  //temperature is low
					printf("temp is %.2f\n",temp_value);
					LED2_ON();
		        	}
		  	}
		  }
		  else{
                      pthread_join(thread, (void **)&sleep_flag);
		  }
		}
		// if not sleep.
		else{
			if(!window_flag){ //if window is down 
				send_from_server("up");
				window_flag = 1;
			}

			sleep_flag = 0;
		}
	}
	
	return 0;
}



