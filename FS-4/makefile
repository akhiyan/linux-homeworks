all: test

redirect_cin: redirect_cin.o | .gitignore
	g++ $^ -o $@ 

redirect_cin.ii: redirect_cin.cpp
	g++ -E $^ -o $@

redirect_cin.s: redirect_cin.ii
	g++ -S $^ -o $@

redirect_cin.o: redirect_cin.s
	g++ -c $^ -o $@
.gitignore:
	echo "redirect_cin" > $@

clean:
	rm *.ii *.s *.o *.out redirect_cin .gitignore

test: redirect_cin 
	./redirect_cin < test.in > test.out
	diff test.out test.expected > /dev/null 2>&1 && echo PASSED || echo FAILED
                                
