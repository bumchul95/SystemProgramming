#include <stdio.h>
#include <time.h>

double timer(){
	int j=1;
	clock_t start,finish;
	double duration=0.0;
	start=clock();
	while(j){	
		finish=clock();
		duration=(double)(finish-start)/CLOCKS_PER_SEC;
		if(duration >3){
			j=0;
		}	
	}

	return duration;
}
