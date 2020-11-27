CC=g++
OBJS=prog.o average.o record.o
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

clean:
	@rm -f $(OBJS)
	@rm -f $(PROGRAM)

# Add a new .h and .cpp file with a function that, given an array of
# student records, counts the # of students with an above-average grade
