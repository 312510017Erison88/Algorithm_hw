CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --show-leak-kinds=all --track-origins=yes 

all: 0811549

delrepeat.o: longest_common_sequence.cpp
	g++ -c longest_common_sequence.cpp
0811549: longest_common_sequence.o
	g++ -o 0811549 longest_common_sequence.o

do:
	./0811549 input.in output.out

diff:
	diff -w output1.out an1 > diff1

check:
	$(CHECKCC) $(CHECKFLAGS) ./0811549 input.in output.out

clean:
	rm -rf *.o 0811549 *.out