#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
//#include "apue.h"
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>

volatile int x=0;
extern int makethread(void *(*fn)(void *), void *arg);

void* func(void *arg){
	pthread_t tid;
    tid = pthread_self();
	printf("executing thread id=%lu\n",tid);
	int *t=(int*)arg;
	(*t)++;
	return NULL;
}
int main(){
	printf("return with %lu\n",makethread(func,&x));
#ifdef SLEEP
	sleep(1); //wait for detached threads finish
#endif

	printf("x=%d\n",x);
	return 0;

}