#include <stdlib.h>
#include <pthread.h>

#define NHASH 9
#define HASH(id) (((unsigned long)id)%NHASH)

struct foo *fh[NHASH];

pthread_mutex_t hashlock = PTHREAD_MUTEX_INITIALIZER;

struct foo {
	int             f_count;
	pthread_mutex_t f_lock;
	int             f_id;
	struct foo     *f_next; /* protected by hashlock */
	/* ... more stuff here ... */
};

struct foo *
foo_alloc(int id) /* allocate the object */
{
	struct foo	*fp;
	int			idx;

	if ((fp = malloc(sizeof(struct foo))) != NULL) {
		fp->f_count = 1;
		fp->f_id = id;
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
			free(fp);
			return(NULL);
		}
		idx = HASH(id);
		printf("id=%d, idx(HASH(id))=%d\n",id, idx);
		pthread_mutex_lock(&hashlock);
		fp->f_next = fh[idx];
		fh[idx] = fp;
		pthread_mutex_lock(&fp->f_lock);
		pthread_mutex_unlock(&hashlock);
		/* ... continue initialization ... */
		pthread_mutex_unlock(&fp->f_lock);
	}
	return(fp);
}

void foo_hold(struct foo *fp) /* add a reference to the object */
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	printf("hold lock: f_count=%d\n",fp->f_count++);
	//do something while holding this lock
	pthread_mutex_unlock(&fp->f_lock);
}

struct foo* foo_find(int id) /* find an existing object */
{
	struct foo	*fp;

	pthread_mutex_lock(&hashlock);
	for (fp = fh[HASH(id)]; fp != NULL; fp = fp->f_next) {
		if (fp->f_id == id) {
			foo_hold(fp);
			break;
		}
	}
	pthread_mutex_unlock(&hashlock);
	return(fp);
}
//fp must be in fp
void foo_rele(struct foo *fp) /* release a reference to the object */
{
	struct foo	*tfp;
	int			idx;

	pthread_mutex_lock(&fp->f_lock);
	if (fp->f_count == 1) { /* last reference */
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_lock(&hashlock);
		pthread_mutex_lock(&fp->f_lock);
		/* need to recheck the condition */
		if (fp->f_count != 1) {
			fp->f_count--;
			pthread_mutex_unlock(&fp->f_lock);
			pthread_mutex_unlock(&hashlock);
			return;
		}
		/* remove fp from list */
		idx = HASH(fp->f_id);
		tfp = fh[idx];
		if (tfp == fp) {
			fh[idx] = fp->f_next; 
		} else {
			while (tfp->f_next != fp)
				tfp = tfp->f_next;
			tfp->f_next = fp->f_next;
		}
		pthread_mutex_unlock(&hashlock);
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	} else {
		fp->f_count--;
		pthread_mutex_unlock(&fp->f_lock);
	}
}

void hash_print(){
	for(int i=0;i<NHASH;i++){
		printf("[%.2d]:",i);
		if(fh[i]==NULL){
			printf("<NULL>\n");
		}
		else{
			struct foo* temp=fh[i];
			while(temp){
				printf("<%x: %d>",temp,temp->f_id);
				if(temp->f_next){
					printf("-->");
				}else{
					printf("\n");
					break;
				}
				temp=temp->f_next;
			}
		}
	}

}

int main(){
	foo_alloc(1);
	foo_alloc(10);
	foo_alloc(19);
	struct foo* temp;
	hash_print();
	
/*
	if((temp=foo_find(1))==NULL){
		printf("cannot find an existing object for id=%d\n",1);
	}
	else{
		printf("find an existing object for id=%d at addr=%x\n ",1,temp);
	}
*/	
	return 0;
}