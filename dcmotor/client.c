#include <stdio.h>
#include <sys/socket.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>

int main(void){
	int sockfd;
	char* button=malloc(sizeof(char)*10);
	struct sockaddr_in servaddr;	
	if((sockfd=socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket create fail");
		exit(1);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family= AF_INET;
	servaddr.sin_port=htons(4004);
	servaddr.sin_addr.s_addr=inet_addr("192.168.0.238");

	sleep(1);
	printf("test..1 \n");
	int ret;
	while(1){
	  scanf("%s", button);
	  ret= sendto(sockfd, button, strlen(button)+1, 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	  printf("send msg with %d bytes \n", ret);
	
	}
	return 0;
}
