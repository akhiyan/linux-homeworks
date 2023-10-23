#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFF_SIZE 10

int main (int argc, char** argv){
	if (argc < 2){
		std::cerr << "File path is not given" << std::endl;
	       	exit(1);
	}

	char* pathname = argv[1];
	int fd = open(pathname, O_WRONLY);
	if (fd<0){
		std::cerr << strerror(errno) << std::endl;
	       	exit(errno);
	}

	char* buffer = new char[BUFF_SIZE];
	for (int i = 0; i < BUFF_SIZE+1; ++i){
		buffer[i] = '\0';
	}	

	struct stat statbuf;
	fstat(fd, &statbuf);
	int file_size = statbuf.st_size;

	int count=0;
	while (count < file_size){
		int writtenBytes = write(fd, buffer, BUFF_SIZE);
		if (writtenBytes < 0){
            		std::cerr << strerror(errno) << std::endl;
            		exit(errno);
        	}
		count += writtenBytes;
	}
	
	int removed_file = unlink(pathname);
	if(removed_file < 0){
		std::cout << strerror(errno) << std::endl;
		exit(errno);
	}

	delete buffer;
	return 0;
}

