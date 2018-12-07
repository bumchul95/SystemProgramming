#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <fcntl.h>
#include <pthread.h>

pthread_t thread;

int thread_start_flag = 1;
int thr_id;

#define NODE_NAME "/dev/bed_touch_dev"

void *pir_thread(void * unuse) {
	int fd;
	int ret;
	int stat = 0;
	int cnt = 0;

	fd = open(NODE_NAME, O_RDWR);

	while(thread_start_flag) {
		
		ret = read(fd, &stat, sizeof(stat));

		if(stat == 1)
			cnt++;

		printf("-----> %dbyte read, stat = %d cnt=%d\n", ret, stat, cnt);
		usleep(100000);
	}

	close(fd);

	printf("### Terminate thread...\n");
	pthread_exit((void *)fd);
}

int main(int argc, char * argv[])
{
	int status, i;

	thr_id = pthread_create(&thread, 0, pir_thread, 0);

	if(thr_id < 0)
	{
		printf("#### ERROR pthread_create\n");
		exit(0);
	}

	for(i =0; i<10; ++i){
		printf("count = %d\n", 9-i);
		sleep(1);
	}

	thread_start_flag = 0;
	pthread_join(thread, (void **)&status);
	printf("### Exit program, status = %d\n", status);

	exit(0);
}


