#include <iostream>
#include <thread>
#include <mutex>
#include <ctime>

double time_spent = 0.0;
const unsigned int first = 100000000; //100 000 000
const unsigned int last = 399999999; //399 999 999
long long unsigned int result = 0;

std::mutex tmutex;

void sum(int me)
{
	int part = me;
	int offset = 75000000;
	//std::cout << "part: " << part << ", first: " << first+part*75000000 << ", last: " << last-(3-part)*offset << "\n";
	
	long long unsigned int res = 0;
	for (int i = first+part*75000000; i <= last-(3-part)*offset; i++)
    {
        res = res + i;
    }
    
    tmutex.lock();
    //std::cout << "result after sum " << part << ": " << res << "\n";    
    result = result + res;
    //std::cout << "result after sum " << part << ": " << result << "\n";  
    tmutex.unlock();
}

int main()
{
	std:: thread threads[4];
	
	clock_t begin = clock();
	for (int i = 0; i < 4; i++)
    {
    	threads[i] = std::thread(sum, i);
    }   
    for (int i = 0; i < 4; i++)
    {
    	threads[i].join();
    }
    clock_t end = clock();
    time_spent += (double)(end - begin)/CLOCKS_PER_SEC;
    
    std::cout << "Result: " << result << "\nTime spent: " << time_spent << " sec\n";
    
    return 0;
}
