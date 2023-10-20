all: test

simple_copy: simple_copy.o | .gitignore
	g++ $^ -o $@ 

simple_copy.ii: simple_copy.cpp
	g++ -E $^ -o $@

simple_copy.s: simple_copy.ii
	g++ -S $^ -o $@

simple_copy.o: simple_copy.s
	g++ -c $^ -o $@
.gitignore:
	echo "simple_copy" > $@

clean:
	rm *.ii *.s *.o *.out simple_copy .gitignore

test: simple_copy
	./simple_copy < test.in > test.out
	diff test.out test.expected > /dev/null 2>&1 && echo PASSED || echo FAILED

