all: test

read_file: read_file.o | .gitignore
	g++ $^ -o $@ 

read_file.ii: read_file.cpp
	g++ -E $^ -o $@

read_file.s: read_file.ii
	g++ -S $^ -o $@

read_file.o: read_file.s
	g++ -c $^ -o $@
.gitignore:
	echo "read_file" > $@

clean:
	rm *.ii *.s *.o *.out read_file .gitignore

test: read_file 
	./read_file < test.in > test.out
	diff test.out test.expected > /dev/null 2>&1 && echo PASSED || echo FAILED
                                
