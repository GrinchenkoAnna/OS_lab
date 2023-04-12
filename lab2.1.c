#include <stdio.h>
#include <time.h>

int main()
{
    double time_spent = 0.0;
    const unsigned int first = 100000000; //100 000 000
    const unsigned int last = 399999999; //399 999 999
    long long unsigned int result = 0;
    
    clock_t begin = clock();
    for(int i = first; i <= last; i++)
    {
        result = result + i;
    }
    clock_t end = clock();
    time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
    
    printf("Result: %llu\nTime spent: %f sec\n", result, time_spent);
    
    return 0;
}

