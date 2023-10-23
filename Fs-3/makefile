all: test

hacker_rm: hacker_rm.o | .gitignore
	g++ $^ -o $@ 

hacker_rm.ii: hacker_rm.cpp
	g++ -E $^ -o $@

hacker_rm.s: hacker_rm.ii
	g++ -S $^ -o $@

hacker_rm.o: hacker_rm.s
	g++ -c $^ -o $@
.gitignore:
	echo "hacker_rm " > $@

clean:
	rm *.ii *.s *.o *.out hacker_rm  .gitignore

test: hacker_rm  
	./hacker_rm  < test.in > test.out
	diff test.out test.expected > /dev/null 2>&1 && echo PASSED || echo FAILED
                                
