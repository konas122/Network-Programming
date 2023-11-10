#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void* thread_main(void *arg);


int main(int argc, char *argv[]) {
	pthread_t t_id;
    int thread_param = 5;
    void *thr_ret;

    if(pthread_create(&t_id, NULL, thread_main, (void *)&thread_param) != 0) {
		puts("pthread_create() error");
		return -1;
	}

    // 这里调用`pthread_join`，`main`函数将等待`ID`保存`t_id`变量中的线程终止
	if(pthread_join(t_id, &thr_ret)!=0) {
		puts("pthread_join() error");
		return -1;
	}

	printf("Thread return message: %s \n", (char*)thr_ret);
	free(thr_ret);
	return 0;
}


void* thread_main(void *arg) {
	int i;
    int cnt = *((int *)arg);
    char *msg = (char *)malloc(sizeof(char) * 50);
    strcpy(msg, "Hello, I'am thread~ \n");

    for(i = 0; i < cnt; i++) {
		sleep(1);
        puts("running thread");
    }
    // 这里的返回值将传到上面的`thr_ret`变量中
    return (void *)msg;
}
