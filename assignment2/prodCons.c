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

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;
int theProduct = 0;
int run = 1;

// Print the value placed in the buffer by the producer
void consume(int i, int pid){
    printf("%i Thread- %i\n", i, pid);
}

// Create a value for the producer.
int produce(int pid){
    printf("%i Thread- %i\n", theProduct+1, pid);
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
    int buf;
    // Loop forever
    while(run) {
        // lock the mutex
        pthread_mutex_lock(&the_mutex);
        // while buffer is not empty, loop and call the consumer
        while(buffer != 0)pthread_cond_wait(&condp, &the_mutex);
        // get a number from produce() and put it in the buffer
        buf = produce(pthread_self());
        put(buf);
        // dirty exit since the consumer would hang with no producer thread to signal
        if(theProduct == 21){run = 0;}
        // signal the consumer
        pthread_cond_signal(&condc);
        // unlock the mutex
        pthread_mutex_unlock(&the_mutex);
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
        // lock the mutex
        pthread_mutex_lock(&the_mutex);
        // while the buffer is empty, loop and call the producer
        while(buffer == 0)pthread_cond_wait(&condc, &the_mutex);
        // get the number from the buffer and send it to consume()
        buf = get();
        consume(buf, pthread_self());
        // clear the buffer
        buffer = 0;
        // dirty exit since the consumer would hang with no producer thread to signal
        if(theProduct == 21){run = 0;}
        // signal the producer
        pthread_cond_signal(&condp);
        // unloxk the mutex
        pthread_mutex_unlock(&the_mutex);
    }
    printf("--Done with Consumer!\n");
    pthread_exit(0);
}

int main(int argc, char **argv)
{
    // declare the producer and consumer threads
    pthread_t prod, cons;
    // set the mutex to 0
    pthread_mutex_init(&the_mutex, 0);
    // initialize the condition variable pointers
    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);
    // create the threads
    pthread_create(&cons, 0, consumer, 0);
    pthread_create(&prod, 0, producer, 0);
    // join the threads
    pthread_join(prod, 0);
    pthread_join(cons, 0);
    // cleanup
    printf("--Done!  Cleaning up!\n\n");
    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);

    return 0;
}
