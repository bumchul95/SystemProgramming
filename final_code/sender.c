#include <stdio.h>
#include <sys/socket.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>

void send_from_server(char str[10]){

	int sockfd;
	struct sockaddr_in servaddr;	

	printf("send message: %s\n", str);

	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("socket create fail");
		exit(1);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(4004);
	servaddr.sin_addr.s_addr = inet_addr("192.168.0.238");
	sleep(1);

	printf("server open\n");
	int ret;

	ret = sendto(sockfd, str, strlen(str)+1, 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("send msg with %d bytes \n", ret);

	return;
}
