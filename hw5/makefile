CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --show-leak-kinds=all --track-origins=yes 

all: 0811549

delrepeat.o: Binary_Search_Tree.cpp
	g++ -c Binary_Search_Tree.cpp
0811549: Binary_Search_Tree.o
	g++ -o 0811549 Binary_Search_Tree.o

do:
	./0811549 input.in output.out

diff:
	diff -w output.out an1 > diff1

check:
	$(CHECKCC) $(CHECKFLAGS) ./0811549 input.in output.out

clean:
	rm -rf *.o 0811549 *.out