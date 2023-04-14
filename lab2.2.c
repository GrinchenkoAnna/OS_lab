#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

double time_spent = 0.0;
const unsigned int first = 100000000; //100 000 000
const unsigned int last = 399999999; //399 999 999
long long unsigned int result = 0;
unsigned int parts[4] = {0, 1, 2, 3};
pthread_t threads[4];
pthread_mutex_t mutex;

void* sum(void* me)
{
	int part = *((int*)me);
	int offset = 75000000;
	//printf("part: %d, first: %d, last: %d\n", part, first+part*75000000, last-(3-part)*offset);
	
	long long unsigned int res = 0;
	for (int i = first+part*75000000; i <= last-(3-part)*offset; i++)
    {
        res = res + i;
    }
    
    pthread_mutex_lock(&mutex);
    //printf("result after sum %d: %llu\n", part, res);
    result = result + res;
    //printf("result in thread %d: %llu\n", part, result);
    pthread_mutex_unlock(&mutex);
}

int main()
{
	pthread_attr_t attrs; //атрибуты потока
	if (pthread_attr_init(&attrs) != 0)
	{
		perror("Cannot initialize attributes");
		abort();
	}
	if (pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE) != 0)
	{
		perror("Error in setting attributes");
		abort();
	}
	
	clock_t begin = clock();
	for (int i = 0; i < 4; i++)
	{
		if (pthread_create(&threads[i], &attrs, sum, &parts[i]) != 0)
		{
			perror("Cannot create a thread");
			abort();
		}
	}
	pthread_attr_destroy(&attrs);
    
    for (int i = 0; i < 4; i++)
    {
    	if (pthread_join(threads[i], NULL) != 0)
		{
			perror("Cannot join a thread");
			abort();
		}
    }    
    clock_t end = clock();
    time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
    
    printf("Result: %llu\nTime spent: %f sec\n", result, time_spent);
    
    return 0;
}



