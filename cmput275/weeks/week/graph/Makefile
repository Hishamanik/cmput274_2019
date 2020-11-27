CC=g++
CFLAGS=-c -Wall -O2 -std=c++11
LFLAGS=
PROGS= digraph_test digraph_builder
OBJS= digraph.o digraph_test.o digraph_builder.o

# executable targets
all: digraph_test digraph_builder

digraph_builder: digraph_builder.o digraph.o
	$(CC) digraph_builder.o digraph.o -o digraph_builder $(LFLAGS)

digraph_test: digraph_test.o digraph.o
	$(CC) digraph_test.o digraph.o -o digraph_test $(LFLAGS)

# object targets
digraph_builder.o: digraph_builder.cpp digraph.h
	$(CC) digraph_builder.cpp -o digraph_builder.o $(CFLAGS)

digraph_test.o: digraph_test.cpp digraph.h
	$(CC) digraph_test.cpp -o digraph_test.o $(CFLAGS)

digraph.o: digraph.cpp digraph.h
	$(CC) digraph.cpp -o digraph.o $(CFLAGS)

clean:
	@rm $(OBJS) $(PROGS)
