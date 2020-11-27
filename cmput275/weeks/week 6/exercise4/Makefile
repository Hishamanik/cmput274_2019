CC=g++
LFLAGS=
CFLAGS=-c -Wall -O2
OBJS=exercise4.o 
PROGS=exercise4 

all: $(PROGS)

exercise4: exercise4.o
	$(CC) exercise4.o -o exercise4 $(LFLAGS)

exercise4.o: exercise4.cpp linked_list.h
	$(CC) exercise4.cpp -o exercise4.o $(CFLAGS)

clean:
	@rm -f $(PROGS) $(OBJS)