#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
	int fd;
	char buffer[256];
	//strcpy(buffer, "red");
	
	fd = open("/dev/led_dev", O_RDWR | O_NONBLOCK);
	while(1){
	strcpy(buffer, "red\0");
	write(fd, buffer, strlen(buffer));
	sleep(1);
	}
	close(fd);
	return 0;
}
