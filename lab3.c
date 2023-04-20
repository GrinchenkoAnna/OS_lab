#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_spinlock_t lock;
pthread_spinlock_t lock1;
pthread_spinlock_t lock2;
char sh[6];
int counter = 0;
void* Thread(void* pParams);

int main(void)
{
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, &Thread, NULL);
	
	pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
	//pthread_spin_init(&lock1, PTHREAD_PROCESS_PRIVATE);
	//pthread_spin_init(&lock2, PTHREAD_PROCESS_PRIVATE);
	
	while(counter < 5000) 
	{ 
		printf("%s %d\n", sh, counter); 		
	}	
	
	return 0;
}

void* Thread(void* pParams)
{
	
	while (1)
	{	
		if(counter%2)
		{
			pthread_spin_lock(&lock);
			sh[0]='H';
			sh[1]='e';
			sh[2]='l';
			sh[3]='l';
			sh[4]='o';
			sh[5]='\0';
			pthread_spin_unlock(&lock);
		}
		else
		{
			pthread_spin_lock(&lock);
			sh[0]='B';
			sh[1]='y';
			sh[2]='e';
			sh[3]='_';
			sh[4]='u';
			sh[5]='\0';
			pthread_spin_unlock(&lock);
		}
		//pthread_spin_lock(&lock);
		counter++;
		//pthread_spin_unlock(&lock);	
	}
	return NULL;
}
