CC=g++
LFLAGS=
CFLAGS=-c -Wall -O2
OBJS=listtest.o hashtest.o
PROGS=listtest hashtest

all: $(PROGS)

listtest: listtest.o
	$(CC) listtest.o -o listtest $(LFLAGS)

hashtest: hashtest.o
	$(CC) hashtest.o -o hashtest $(LFLAGS)

listtest.o: listtest.cpp linked_list.h
	$(CC) listtest.cpp -o listtest.o $(CFLAGS)

hashtest.o: hashtest.cpp hash_table.h linked_list.h
	$(CC) hashtest.cpp -o hashtest.o $(CFLAGS)

clean:
	@rm -f $(PROGS) $(OBJS)
