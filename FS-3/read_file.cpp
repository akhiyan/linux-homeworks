#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10

int main(int argc, char* argv[]){
    if (argc < 2){
        std::cerr << "File path is not given" << std::endl;
        exit(1);
    }
    
    char* name = argv[1];
    int fd = open(name, O_RDONLY);
    if (fd<0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    char* buff = new char[BUFFER_SIZE+1];
    while(true){
        int readBytes = read(fd, buff, BUFFER_SIZE);
        if (readBytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
        if(readBytes == 0){
            break;
        }
        buff[readBytes]='\0';
        std::cout << buff;
    }
    
    int closedFile = close(fd);
    if(closedFile < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    
    delete buff;
    return 0;
}
