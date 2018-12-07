#include <stdio.h>
#include <sys/socket.h>
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include <wiringPi.h>

#define MOTOR1A 1
#define MOTOR1B 2

#define BUFF_SIZE 1024

int main(void){
	int sock;
	int client_addr_size;
	int rcv_data;
	struct sockaddr_in server_addr;	
	struct sockaddr_in client_addr;

	char buff_rcv[BUFF_SIZE+5];
	char buff_snd[BUFF_SIZE+5];
	
 	if(wiringPiSetup()==-1){
		return -1;
	}

	pinMode(MOTOR1A,OUTPUT);
	pinMode(MOTOR1B,OUTPUT);

	if((sock=socket(AF_INET,SOCK_DGRAM,0))<0){
		perror("socket create fail");
		exit(1);
	}

	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(4004);
	server_addr.sin_addr.s_addr=inet_addr("192.168.23.132");
	
	if( -1 == bind(sock,(struct sockaddr*)&server_addr,sizeof(server_addr)))
	{
		perror("bind is error");
		exit(1);
	}

	sleep(2);
	int j=0;
	while(1){
	  printf("test..i\n");
	  rcv_data=recvfrom(sock,buff_rcv,BUFF_SIZE,0,(struct sockaddr*)&client_addr,sizeof(client_addr));
	  printf("receive is %s ,%d \n",buff_rcv,rcv_data);
	  if(strcmp(buff_rcv,"on")==0){

	  	for(j=0;j<10;j++){
		  digitalWrite(MOTOR1A,1);
		  digitalWrite(MOTOR1B,0);

		  delay(1000);

		  digitalWrite(MOTOR1A,0);
		  digitalWrite(MOTOR1B,0);
 		  
		  delay(1000);	
		}
	  }
	  //ret= sendto(sockfd,(const char*)hello,strlen(hello),0,(const struct sockaddr *)&servaddr,sizeof(servaddr));
	 
	  //printf("send msg with %d bytes \n",ret);
	}

	return 0;

}
