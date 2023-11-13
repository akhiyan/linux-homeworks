all: do-command

do-command: do-command.o
	g++ $< -o $@

do-command.ii: do-command.cpp
	g++ -E $< -o $@

do-command.s: do-command.ii
	g++ -S $< -o $@

do-command.o: do-command.s
	g++ -c $< -o $@ 

clean:
	rm *.ii *.s *.o *.out do-command

