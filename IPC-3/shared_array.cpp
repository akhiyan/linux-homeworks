// #include  <iostream>
// #include <string.h>
// #include <sys/mman.h>
// #include <sys/stat.h> 
// #include <fcntl.h> 
// #include <errno.h>
// #include <semaphore.h>
// #include <unistd.h>
// #include <sys/types.h>


// class shared_array{
// private:
//     std::string array_name;
//     int size;
//     int* array;
//     sem_t* sem;

#include "shared_array.h"

shared_array::shared_array(std::string array_name, int size)
{
    this->array_name = array_name;
    this->size = size;

    array_name += std::to_string(size);

    int fd = shm_open(array_name.c_str(), O_CREAT | O_RDWR, 0644);
    if(fd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int truncate_result = ftruncate(fd, size);
    if(truncate_result < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int length = size * sizeof(int);
    void* map = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED ,fd, 0);
    if(map == MAP_FAILED){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    array = static_cast<int*>(map);

    // int init_result = sem_init(sem,1,1);
    // if(init_result < 0){
    //     std::cerr << strerror(errno) << std::endl;
    //     exit(errno);
    // }

    int close_result = close(fd);
    if(close_result < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
}
    
int& shared_array::operator[](int index){
    return array[index];
}

// void shared_array::s_wait(){
//     int waiting_result = sem_wait(sem);
// }

// void shared_array::s_post(){
//     sem_post(sem);
// }

shared_array::~shared_array(){

    // int dest_result = sem_destroy(sem);
    // if(dest_result < 0){
    //     std::cerr << strerror(errno) << std::endl;
    //     exit(errno);
    // }

    int unmap_result = munmap(array, size*sizeof(int));
    if(unmap_result < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
}

