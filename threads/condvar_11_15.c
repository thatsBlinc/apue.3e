#include <pthread.h>

struct msg {
	struct msg *m_next;
	/* ... more stuff here ... */
};

struct msg *workq;

pthread_cond_t qready = PTHREAD_COND_INITIALIZER;

pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void
process_msg(void)
{
	struct msg *mp;

	for (;;) {
		pthread_mutex_lock(&qlock);
		//qlock is released when enter
		while (workq == NULL)
			pthread_cond_wait(&qready, &qlock);
		mp = workq;
		workq = mp->m_next;
		printf("processing msg: %x\n",mp);
		pthread_mutex_unlock(&qlock);
		//qlock locked up again when exit
		/* now process the message mp */
	}
}

void
enqueue_msg(struct msg *mp)
{
	pthread_mutex_lock(&qlock);
	mp->m_next = workq;
	workq = mp;
	printf("enqueueing msg: %x\n",mp);
	pthread_mutex_unlock(&qlock);
	pthread_cond_signal(&qready);
}


int main(){
	

}