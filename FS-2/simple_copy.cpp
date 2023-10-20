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
    if (argc < 3){
        std::cerr << "File path is not given" << std::endl;
        exit(1);
    }
    
    char* source = argv[1];
    int source_fd = open(source, O_RDONLY);
    if (source_fd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    char* dest = argv[2];
    int dest_fd = open(dest, O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (dest_fd < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }


    char* buff = new char[BUFFER_SIZE+1];
    while(true){
        int readBytes = read(source_fd, buff, BUFFER_SIZE);
        if (readBytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
        if(readBytes == 0){
            break;
        }
        buff[readBytes]='\0';
       
       	int writenBytes = write(dest_fd, buff, BUFFER_SIZE);
	if (writenBytes < 0){
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }
	if(readBytes == 0){
            break;
        }	
    }
    
    int closedSourceFile = close(source_fd);
    if(closedSourceFile < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int closedDestFile = close(dest_fd);
    if(closedDestFile < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }
    
    delete buff;
    return 0;
}
