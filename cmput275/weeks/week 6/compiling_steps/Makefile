CC=g++
OBJS=prog.o average.o record.o count.o
CFLAGS=-c -Wall -O2
LFLAGS=-static
PROGRAM=prog

$(PROGRAM): $(OBJS)
	$(CC) $(OBJS) -o $(PROGRAM) $(LFLAGS)

prog.o: prog.cpp printclass.h average.h record.h
	$(CC) prog.cpp -o prog.o $(CFLAGS)

average.o: average.cpp average.h record.h
	$(CC) average.cpp -o average.o $(CFLAGS)

record.o: record.cpp record.h
	$(CC) record.cpp -o record.o $(CFLAGS)

count.o: count.cpp count.h record.h average.h
	$(CC) count.cpp -o count.o $(CFLAGS)

clean:
	@rm -f $(OBJS)
	@rm -f $(PROGRAM)
