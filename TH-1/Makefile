all: array-summary

array-summary: array-summary.o
	g++ $< -o $@

array-summary.ii: array-summary.cpp
	g++ -E $< -o $@

array-summary.s: array-summary.ii
	g++ -S $< -o $@

array-summary.o: array-summary.s
	g++ -c $< -o $@ 

clean:
	rm *.ii *.s *.o *.out array-summary

