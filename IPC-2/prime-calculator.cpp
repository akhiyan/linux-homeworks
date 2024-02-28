#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <cstring>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

bool is_prime(int n){
    for(int i = 2; i <= n/2; ++i){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

int m_th_prime_number(int m){
    int i = 1;
    while(m != 0){
        ++i;
        if(is_prime(i)){
            --m;
        }
    }
    
    return i;
}

int main(){

    int pipefd_1[2];
    int pipefd_2[2];
    
    int pipe_result_1 = pipe(pipefd_1);
    if(pipe_result_1 < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int pipe_result_2 = pipe(pipefd_2);
    if(pipe_result_2 < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int pid = fork();
    
    if(pid < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    if(pid > 0){
        close(pipefd_1[0]);
        close(pipefd_2[1]);
        
        std::string m;
        
        while(true){
            std::cout << "Enter the number " << std::endl;
            std::cin >> m;

            if(m == "exit"){
                return 0;
            }

            int n = std::stoi(m);

            int write_result = write(pipefd_1[1], &n , sizeof(int));
            if(write_result < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            int number;
            int read_result = read(pipefd_2[0], &number, sizeof(int));
            if(read_result < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            std::cout << "m-th prime number is " << number << std::endl;
        }
    }

    if(pid == 0){
        close(pipefd_1[1]);
        close(pipefd_2[0]);
    
        int m;
        while(true){
            int read_result = read(pipefd_1[0], &m, sizeof(int));
            if(read_result < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }

            int number = m_th_prime_number(m);

            int write_result = write(pipefd_2[1], &number, sizeof(int));
            if(write_result < 0){
                std::cerr << strerror(errno) << std::endl;
                exit(errno);
            }
        }
    }

    return 0;
}