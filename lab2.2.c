#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

double time_spent = 0.0;
const unsigned int first = 100000000; //100 000 000
const unsigned int last = 399999999; //399 999 999
long long unsigned int result = 0; //результат вычислений
unsigned int parts[4] = {0, 1, 2, 3}; /*значения аргументов потока*/
pthread_t threads[4]; /*массив с id потоков*/
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; /*исключающий семафор/мьютекс*/

void* sum(void* me)  /*потоковая функция*/
{
	int part = *((int*)me); /*принимает через pthread_create аргумент, после чего переводит его в int и использует для расчетов*/
	int offset = 75000000; /*для расчетов блоков, в которых происходит суммирование*/
	//printf("part: %d, first: %d, last: %d\n", part, first+part*75000000, last-(3-part)*offset);
	
	long long unsigned int res = 0; /*промежуточный результат*/
	for (int i = first+part*75000000; i <= last-(3-part)*offset; i++)
    {
        res = res + i;
    }
    
	/*если не защищать переменную мьютексами, результат не изменится. В данном случае не имеет значения, в какой последовательности было проведено суммирование*/
    //pthread_mutex_lock(&mutex); /*захват потоком исключающего семафора*/
    result = result + res; /*итоговый результат*/
    //pthread_mutex_unlock(&mutex); /*освобождение исключающего семафора*/
}

int main()
{
	pthread_attr_t attrs; //атрибуты потока
	if (pthread_attr_init(&attrs) != 0)
	{
		perror("Cannot initialize attributes");
		abort();
	}
	pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_JOINABLE); /*поток создан как ожидаемый (это значение по умолчанию) - он не удаляется ОС, код его завершения хранится в системе, пока другой поток не вызовет pthread_join, чтобы запросить его значение*/	
	
	clock_t begin = clock();
	for (int i = 0; i < 4; i++) /*создание потоков*/
	{
		/*                  поток        атр.   п.ф.  арг.п.ф.*/
		if (pthread_create(&threads[i], &attrs, sum, &parts[i]) != 0)
		{
			perror("Cannot create a thread");
			abort();
		}
	}
	pthread_attr_destroy(&attrs); /*после создания потоков нет необходимости хранить объект*/
    
    for (int i = 0; i < 4; i++)
    {
    	if (pthread_join(threads[i], NULL) != 0) /*аналог wait() для потоков - блокирует вызывающий процесс до тех пор, пока один из его дочерних процессов не завершится или не произойдет ошибка */
		{
			perror("Cannot join a thread");
			abort();
		}
    }    
    clock_t end = clock();
    time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
    
    printf("Result: %llu\nTime spent: %f sec\n\n", result, time_spent);
    
    return 0;
}



