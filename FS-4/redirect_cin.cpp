#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void initialize(int argc, char** argv)
{
	if (argc < 2){
		std::cerr << "file path is not given" << std::endl;
		exit(1);
	}

	char* pathname = argv[1];
	int fd = open(pathname, O_RDWR);
	if(fd < 0){
		std::cerr << strerror(errno) << std::endl;
		exit(errno);
	}

	int redirected_cin = dup2(fd, 0);
	if(redirected_cin < 0){
		std::cerr << strerror(errno) << std::endl;
		exit(errno);
	}
	int closed = close(fd);
	if(closed < 0){
		std::cerr << strerror(errno) << std::endl;
		exit(errno);
	}
}

int main(int argc, char** argv)
{
       	initialize(argc, argv);
      	
	std::string input;
	std::cin >> input;

	int size = input.size();
	std::string reversed = input;
	for (int i = 0; i < size/2; ++i){
		std::swap(reversed[i],reversed[size-i-1]);
	}
	
	reversed[size+1] = '\0';
	std::cout << reversed << std::endl;

  return 0;
}

