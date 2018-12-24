// Monitor implementation of the Producer/Consumer problem.
// Used a monitor implemenation from Brian Anderson @
// https://gist.github.com/banderson623/5161756
// 
// Jackie Adair
// CST-221 Week2 Assignment Semaphores v Monitors
// 24 Dec 2018


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#include "monitor.h"

int buffer = 0;
int theProduct = 0;
int run = 1;

// Print the value placed in the buffer by the producer
void consume(int i, int pid){
    printf("Consume - %i Thread- %i\n", i, pid);
}

// Create a value for the producer.
int produce(int pid){
    printf("Produce - %i Thread- %i\n", theProduct+1, pid);
    return theProduct++;
}

// Put the value in the buffer
void put(int prod){
    buffer = prod;
}

// return the value from the buffer
int get(){
    int value = buffer;
    buffer = 0;
    return value;
}

void *producer(void *ptr)
{
    int buf;
    // loop forever
    while(run){
        // if the buffer is full, loop
        while(buffer !=0);
        // check to see if monitor is gtg
        if(monitor_Initialized() == 0){
            // block until write is avail
            monitor_StartWrite();
            // set the buffer
            buf = produce(pthread_self());
            put(buf);
            // escape at 20
            if(theProduct == 21){run = 0;}
            // signal writing is complete
            monitor_EndWrite();
        }
    }
    printf("Producer's Done\n");
    pthread_exit(0);
}

void *consumer(void *ptr)
{
    int buf;
    // loop forever
    while(run){
        // if the buffer is empty, loop
        while(buffer == 0);
        // check to see if monitor i gtg
        if(monitor_Initialized() == 0){
            // block until read is safe
            monitor_StartRead();
            // read from buffer
            buf = get();
            consume(buf, pthread_self());
            // escape
            if(theProduct == 21){run = 0;}
            // signal complete with read
            monitor_EndRead();
        }
    }
    printf("Consumer's Done\n");
    pthread_exit(0);
}


int main(int argc, char **argv)
{
    pthread_t prod, cons;
    pthread_create(&cons, 0, consumer, 0);
    pthread_create(&prod, 0, producer, 0);

    pthread_join(prod, 0);
    pthread_join(cons, 0);

    return 0;
}
