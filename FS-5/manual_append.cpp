#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv){
    if (argc < 2){
        std::cerr << "File path is not given" << std::endl;
        exit(1);
    }

    char* name = argv[1];
    int fd = open(name, O_WRONLY);
    if (fd<0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    int duplicate_fd = dup(fd);
    if(duplicate_fd < 0){
    	std::cerr << strerror(errno) << std::endl;
	exit(errno);
    }

    std::string str1 = "first line\n";
    std::string str2 = "second line\n";

    int written_bytes = write(fd, str1.c_str(), str1.size());
    if (written_bytes < 0){
    	std::cerr << strerror(errno) << std::endl;
	exit(errno);
    }

    written_bytes = write(duplicate_fd, str2.c_str(), str2.size());
    if (written_bytes < 0){
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    return 0;
}
