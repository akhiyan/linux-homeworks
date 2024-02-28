all: prime-calculator

prime-calculator: prime-calculator.o
	g++ $< -o $@

prime-calculator.ii: prime-calculator.cpp
	g++ -E $< -o $@

prime-calculator.s: prime-calculator.ii
	g++ -S $< -o $@

prime-calculator.o: prime-calculator.s
	g++ -c $< -o $@ 

clean:
	rm *.ii *.s *.o *.out prime-calculator

