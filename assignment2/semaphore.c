// This solution to the Producer/Consumer problem uses a mutex
// to lock the critical areas that the producer and comsumer share
// Each thread will check the buffer (size = 1) to see if there is
// a value.  If there is, one, the producer will sleep and signal the 
// consumer.  If there is no value, the consumer will signal the producer
// and the sleep.  The producer will place a value and the consumer will
// consume the value if the criteria are met.
//
// Jackie A. Adair
// CST-221 Week 2 Assignment Producer-Consumer
// 23 December 2018

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t buf_mutex, empty_count, fill_count;

int buffer = 0;
int theProduct = 0;
int run = 1;

// Print the value placed in the buffer by the producer
void consume(int i, int pid){
    printf("C-%i Thread- %i\n", i, pid);
}

// Create a value for the producer.
int produce(int pid){
    printf("P-%i Thread- %i\n", theProduct+1, pid);
    return theProduct++;
}

// Put the value in the buffer
void put(int prod){
    buffer = prod;
}

// return the value from the buffer
int get(){
    return buffer;
}

// the producer (is passed the mutex)
void *producer(void *ptr)
{
    int buf = produce(pthread_self());
    // Loop forever
    while(run) {
		printf("Pbuffer = %i\n",buffer);
        // get a number from produce() and put it in the buffer

        while(buffer != 0);
        sem_wait(&empty_count);
        sem_wait(&buf_mutex);

        put(buf);
        // dirty exit since the consumer would hang with no producer thread to signal
        if(theProduct == 21){run = 0;}
        // signal the consumer
        sem_post(&buf_mutex);
        sem_post(&fill_count);

    }
    printf("--Done with Producer!\n");
    pthread_exit(0);
}

// The consumer (passed the mutex)
void *consumer(void *ptr)
{
    int buf;
    // loop forever
    while(run){
		printf("Cbuffer = %i\n",buffer);
		sem_wait(&fill_count);
		sem_wait(&buf_mutex);
        // while the buffer is empty, loop 
        while(buffer == 0);
        // get the number from the buffer and send it to consume()
        buf = get();
        consume(buf, pthread_self());
        // clear the buffer
        buffer = 0;
        // dirty exit since the consumer would hang with no producer thread to signal
        if(theProduct == 21){run = 0;}
        // signal the producer
 		sem_post(&buf_mutex);
		sem_post(&empty_count);
    }
    printf("--Done with Consumer!\n");
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    // declare the producer and consumer threads
    pthread_t prod, cons;
	sem_init(&buf_mutex,0,1);
	sem_init(&fill_count,0,0);
	sem_init(&empty_count,0,1);

    // create the threads
    pthread_create(&cons, 0, consumer, 0);
    pthread_create(&prod, 0, producer, 0);
    // join the threads
    pthread_join(prod, 0);
    pthread_join(cons, 0);

    return 0;
}
