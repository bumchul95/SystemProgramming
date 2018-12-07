#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/kdev_t.h>
#include <string.h>

int main(int argc, char **argv){
	int fd_m;
	int fd_s;
	int fd_b;
	int fd_z;
	int receive;
	int ret;
	int count = 0;
	int wakeupflag = 0;
	char buffer[256];
	fd_b = open("/dev/button_dev", O_RDWR | O_NONBLOCK);
	if(fd_b < 0){
		perror("button open error");
		return -1;
	}
	fd_s = open("/dev/sound_dev", O_RDWR | O_NONBLOCK);
	if(fd_s < 0){
		perror("sound open error");
		return -1;
	}
	fd_m = open("/dev/moter_dev", O_RDWR | O_NONBLOCK);
	if(fd_m < 0){
		perror("moter open error");
		return -1;
	}
	fd_z = open("/dev/buzzer_dev", O_RDWR | O_NONBLOCK);
	if(fd_z < 0){
		perror("buzzer open error");
		return -1;
	}
	
	for(;;){
		ret = read(fd_b, &receive, 4);
		printf("%d\n", receive);
		usleep(100 * 1000);
		if(receive == 1){
			printf("Wake up mode\n");
			break;
		}
	}
	for(;;){
		if(wakeupflag == 1)
			break;
		write(fd_z, buffer, strlen(buffer));
		ret = read(fd_s, &receive, 4);
		printf("Wake up!!! %d\n", receive);
		sleep(1);
		if(receive == 0)
			count++;
		if(count == 5){
			write(fd_m, buffer, strlen(buffer));
			printf("bed is up!!\n");
			receive = 0;
			for(;;){
				write(fd_z, buffer, strlen(buffer));
				ret = read(fd_b, &receive, 4);
				printf("%d\n", receive);
				usleep(100 * 1000); // fast sound for this
				if(receive == 1){
					printf("bed, sound down\n");
					wakeupflag = 1;
					break;
				}
			}
		}
	}

	close(fd_s);
	close(fd_m);
	close(fd_b);
	close(fd_z);
	return 0;
}
