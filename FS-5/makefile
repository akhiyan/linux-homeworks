all: test

manual_append: manual_append.o | .gitignore
	g++ $^ -o $@ 

manual_append.ii: manual_append.cpp
	g++ -E $^ -o $@

manual_append.s: manual_append.ii
	g++ -S $^ -o $@

manual_append.o: manual_append.s
	g++ -c $^ -o $@
.gitignore:
	echo "manual_append" > $@

clean:
	rm *.ii *.s *.o *.out manual_append .gitignore

test: manual_append 
	./manual_append < test.in > test.out
	diff test.out test.expected > /dev/null 2>&1 && echo PASSED || echo FAILED
                                
