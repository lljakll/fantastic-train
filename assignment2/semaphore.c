// Jackie Adair
// CST 221
// Semaphores and Monitors
// 24 December 2018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>


pthread_t *producers;
pthread_t *consumers;

sem_t buf_mutex,empty_count,fill_count;

int *buf,buf_pos=-1;


int produce(){
	int i = 0;
	int p = 1 + rand()%40;
	printf("Producer - %d \n",p);
	return p;
}


void consume(int p){
	printf("Consumer - %d \n",p);
	
}


void* producer(void *args){

	while(1){
		int p = produce();
		// block until availalbe, lock
		sem_wait(&empty_count);
		sem_wait(&buf_mutex);
		++buf_pos;			// critical section
		*(buf + buf_pos) = p; 
		// unlock and signal
		sem_post(&buf_mutex);
		sem_post(&fill_count);
	}
	
	return NULL;
}


void* consumer(void *args){
	int c;
	while(1){
		// block until available, lock
		sem_wait(&fill_count);
		sem_wait(&buf_mutex);
		c = *(buf+buf_pos); // critical section
		consume(c);
		--buf_pos;
		// unlock and signal
		sem_post(&buf_mutex);
		sem_post(&empty_count);
	}

	return NULL;
}

int main(void){
	
	int i,err;

	srand(time(NULL));

	sem_init(&buf_mutex,0,1);
	sem_init(&fill_count,0,0);
	sem_init(&empty_count,0,1);

	producers = (pthread_t*) malloc(sizeof(pthread_t));

	consumers = (pthread_t*) malloc(sizeof(pthread_t));

	buf = (int*) malloc(sizeof(int));

		pthread_create(producers,NULL,&producer,NULL);


		pthread_create(consumers,NULL,&consumer,NULL);
		
		pthread_join(*producers,NULL);

		pthread_join(*consumers,NULL);
	

	return 0;
}
