#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <bits/stdc++.h>
#include <chrono>

void do_command(char** argv){

	auto start = std::chrono::high_resolution_clock::now();
	
	pid_t pid = fork();
	if(pid == -1){
		std::cerr << strerror(errno) << std::endl;
		exit(errno);
	}

	if (pid == 0){
		int execute_command = execvp(argv[1], &argv[1]);

		if(execute_command < 0){
			std::cerr << strerror(errno) <<std::endl;
			exit(errno);
		}
	} else{
		int wstatus;
		pid_t waiting_pid = waitpid(pid, &wstatus, 0);
		if (waiting_pid == -1){
			 std::cerr << strerror(errno) << std::endl;
			 exit(errno);
		}

		auto end = std::chrono::high_resolution_clock::now();
		double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		duration *= 1e-9;
	
		std::cout << "Command completed with " << WEXITSTATUS(wstatus) << " exit code and took " << duration << " seconds" << std::endl;
	}
}

int main(int argc, char** argv){
	
	if(argc < 2){
		std::cerr << "Not enough arguments" << std::endl;
		exit(1);
	}

	do_command(argv);
}

