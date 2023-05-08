CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --show-leak-kinds=all --track-origins=yes 

all: 0811549

delrepeat.o: Dynamic_programming.cpp
	g++ -c Dynamic_programming.cpp
0811549: Dynamic_programming.o
	g++ -o 0811549 Dynamic_programming.o

do:
	./0811549 input.in output.out

diff:
	diff -w output1.out an1 > diff1

check:
	$(CHECKCC) $(CHECKFLAGS) ./0811549 input.in output.out

clean:
	rm -rf *.o 0811549 *.out