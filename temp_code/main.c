#include <stdio.h>
#include <wiringPi.h>
#include "dht11temp.h"
#include "led.h"
#include "motor.h"
#include "touch.h"
#include "timer.h"
#include <unistd.h>


int main(void){
	float temp; 
	while(1) {
		int touch_state=touch();
		if(touch_state==1){
		
		//온도가 20도이상일때 불켜주는거.. 
		temp=read_dht11_dat();
			
		if(temp >0.1){
			if(temp>20.0){
				printf("temp is %.2f\n",temp);
				high();
			}else{
				printf("temp is %.2f\n",temp);
				low();
			}
		//일정시간이 지나면 자는거 thread로 구현해야함
		printf("debug\n"); 
		double time=timer();
		if(time > 3){
			printf("sleep start\n");
		}
	    	}
	}else{ // 터치 안되어있을 경우
		printf("not sleep \n");
	}
		
	}

}

