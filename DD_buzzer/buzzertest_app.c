// gcc -pthread -o buzzertest buzzertest_app.c 
// sudo ./test 1

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/kdev_t.h>
#include <pthread.h> 

#define DEV_PATH "/dev/buzzer_dev"

typedef struct tThread{
 	int fd;
	char buff;
}THREAD;

void *buzzer(void *p){
	THREAD *pp=(THREAD*)p;
	int fd= pp->fd;
	char buff=pp->buff;
	write(fd,&buff,4);
}


int main(int argc, char *argv[]){
	pthread_t p_thread;
	int tid;
	int status;
	char p1[] ="thread_1";
	THREAD st;
	st.fd=0;
	if((st.fd = open(DEV_PATH, O_RDWR | O_NONBLOCK)) <0){
		perror("open()");
		exit(1);
	}
	st.buff = atoi(argv[1]);
	tid=pthread_create(&p_thread,NULL,buzzer,(void *)&st);

	tid=pthread_create(&p_thread,NULL,buzzer,(void *)&st);
	tid=pthread_create(&p_thread,NULL,buzzer,(void *)&st);
	tid=pthread_create(&p_thread,NULL,buzzer,(void *)&st);
	pthread_join(p_thread,(void **)&status);
	printf("result : %d\n",status);
	//write(fd,buff,4);
	printf("Open success! \n");


	
	close(st.fd);
	return 0;
}
