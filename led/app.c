#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
	int fd;
	char buffer[256];
	char green[16] = "1";//
	char blue[16] = "22";
	//strcpy(buffer, "red");
	
	fd = open("/dev/led_dev", O_RDWR | O_NONBLOCK);
	while(1){
	//strcpy(buffer, "red");
	//scanf("%s", red);
	write(fd, green, strlen(green));
	sleep(1);
	}
	close(fd);
	return 0;
}
