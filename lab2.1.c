#include <stdio.h>
#include <time.h>

int main()
{
    double time_spent = 0.0;
    const unsigned int first = 100000000; //100 000 000
    const unsigned int last = 399999999; //399 999 999
    long long unsigned int result = 0; //результат вычислений
    
    clock_t begin = clock(); /*запуск отсчета времени*/
    for(int i = first; i <= last; i++)
    {
        result = result + i;
    }
    clock_t end = clock(); /*конец отсчета времени*/
    time_spent += (double)(end - begin)/CLOCKS_PER_SEC; /*перевод отсчитанного времени в секунды*/
    
    printf("Result: %llu\nTime spent: %f sec\n\n", result, time_spent);
    
    return 0;
}

