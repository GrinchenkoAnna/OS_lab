#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

char sh[6];
pthread_spinlock_t lock;

void* Thread(void* pParams);

int main(void)
{
	pthread_t thread_id;	
	pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);	
	pthread_create(&thread_id, NULL, &Thread, NULL);
	
	
	while(1) { printf("%s\n", sh); }
}

void* Thread(void* pParams)
{
	int counter = 0;
	while(1)
	{
		pthread_spin_lock(&lock);
		if(counter%2)
		{
			sh[0] = 'H';
			sh[1] = 'e';
			sh[2] = 'l';
			sh[3] = 'l';
			sh[4] = 'o';
			sh[5] = '\0';
		}
		else
		{
			sh[0] = 'B';
			sh[1] = 'y';
			sh[2] = 'e';
			sh[3] = '_';
			sh[4] = 'u';
			sh[5] = '\0';
		}
		pthread_spin_unlock(&lock);
		
		//pthread_spin_lock(&lock);
		counter++;
		//pthread_spin_unlock(&lock);
	}
	
	return NULL;
}
