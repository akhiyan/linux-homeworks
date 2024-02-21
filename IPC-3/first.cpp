#include <semaphore>
#include "shared_array.h"

const char *semaphore = "/aaaaa";

int main(){
    shared_array array("test_array",1000);
     sem_t *sem = sem_open(semaphore, O_CREAT | O_EXCL, 0644, 1);
    if (sem == SEM_FAILED) {
        if(errno == EEXIST)
        {
            int sem_un_res = sem_unlink(semaphore);
            if(sem_un_res < 0)
            {
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            sem = sem_open(semaphore, O_CREAT | O_EXCL, 0644, 1);
        }
        else{
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
    }

    while(true){
        sem_wait(sem);
        for(int i = 0; i < 1000; ++i){
            array[i] = 1;
        }
        sem_post(sem);
    }
    return 0;
}
