#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <time.h>

pthread_mutex_t resource1, resource2;
int test=0;
clock_t startTime1, countTime1, startTime2, countTime2;
int timeLeft1, timeLeft2, countDownTime1, countDownTime2 = 0;
countDownTime1, countDonTime2 = 10000;




void *proc1()
{
	printf("This is proc1 using rs1, PID-%lu\n", pthread_self());
	pthread_mutex_lock(&resource1);
 		usleep(200);
		startTime1 = clock();
		timeLeft1 = countDownTime1-startTime1;
		while(timeLeft1>0){
			printf("p1 trying to get rs2...\n");
			pthread_mutex_lock(&resource2);
				test++;
			// if lock success then execute, unlock and terminate
			if(){

			}
			// if lock not success, block until timer runs or resource is avail
			printf("proc1 got rs2!!\n");
			pthread_mutex_unlock(&resource2);

			countTime1 = clock();
			timeLeft1 = timeLeft1-countTime1;
		}
	pthread_mutex_unlock(&resource1);
return 0;
}

void *proc2()
{
	printf("This is proc2 using rs2, PID-%lu\n", pthread_self());
	pthread_mutex_lock(&resource2);
		usleep(200);
		startTime2 = clock();
		printf("p2 trying to get rs1...\n");
		pthread_mutex_lock(&resource1);
			test--;
		printf("proc2 got rs!!\n");
		pthread_mutex_unlock(&resource1);
	pthread_mutex_unlock(&resource2);
return 0;
}

int main(){
	pthread_t t1, t2;
	pthread_mutex_init(&resource1, NULL);
	pthread_mutex_init(&resource2, NULL);

	pthread_create(&t1, NULL, proc1, NULL);
	pthread_create(&t2, NULL, proc2, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	// will never arrive here
	pthread_mutex_destroy(&resource1);
	pthread_mutex_destroy(&resource2);
}
