#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv){
	int fd;
	char buffer[256];
	fd = open("/dev/moter_dev", O_RDWR | O_NONBLOCK);
	
	write(fd, buffer, strlen(buffer));
	printf("tick...\n");
	

	close(fd);	

	return 0;
}
