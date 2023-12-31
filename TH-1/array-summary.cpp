#include <iostream>
#include <pthread.h>
#include <string.h>
#include <errno.h>
#include <chrono>
#include <random>

struct local_sum_arg
{
    int* array;
    int start;
    int end;
};

void* local_sum(void* arg)
{
    local_sum_arg* part = (local_sum_arg*) arg;
    int sum = 0;
    for(int i = part->start; i < part->end; ++i)
    {
        sum += part->array[i];
    }

    return new int(sum);
}

int main(int argc, char** argv){
	if(argc < 3){
		std::cerr << "Not enough arguments";
		exit(1);
	}

	int N = std::stoi(argv[1]);
	int M = std::stoi(argv[2]);
	
	int* array = new int[N];

	for(int i = 0; i < N; ++i){
		array[i] = rand();
	}
	
	auto start = std::chrono::high_resolution_clock::now();
	
	int sum = 0;
	for(int i = 0; i < N; ++i){
		sum += array[i];
	}

	auto end = std::chrono::high_resolution_clock::now();
	double duration_with_loop = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	duration_with_loop *= 1e-9;
	
	start = std::chrono::high_resolution_clock::now();

	pthread_t* threads = new pthread_t[M];
	local_sum_arg** array_of_args = new local_sum_arg*[M];
    	for(int i = 0; i < M; ++i){
	
		array_of_args[i] = new local_sum_arg;
 	        array_of_args[i]->array = array;
	        array_of_args[i]->start = i * (N / M);
       	 	array_of_args[i]->end = std::min(array_of_args[i]->start + (N / M), N);
        
		int result = pthread_create(&threads[i], NULL, local_sum, array_of_args[i]);
        
		if(result != 0)
        	{
            		std::cerr << strerror(result) << std::endl;
		       	exit(result);
        	}
    	}

 	for(int i = 0; i < M; ++i)
    	{
        	void* return_value;
        	int result = pthread_join(threads[i], &return_value);
        	int* local_sum_result = (int*)return_value;
       		sum += *local_sum_result;
        
		delete local_sum_result;
        	delete array_of_args[i];
    	}

    	end = std::chrono::high_resolution_clock::now();
        double duration_with_threads = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	duration_with_threads *= 1e-9;

	std::cout << "Time spent without threads " << duration_with_loop << std::endl;
	std::cout << "Time spent with " << M << " threads " << duration_with_threads << std::endl;

	delete[] array_of_args;
	delete[] array;
	return 0;
}
