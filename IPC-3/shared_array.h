#ifndef SHARED_ARRAY
#define SHARED_ARRAY

#include  <iostream>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h> 
#include <fcntl.h> 
#include <errno.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/types.h>

class shared_array{
private:
    std::string array_name;
    int size;
    int* array;
    // sem_t* sem;

public:
    shared_array(std::string, int);
    // void s_wait();
    // void s_post();
    int& operator[](int);
    ~shared_array();
};

#endif