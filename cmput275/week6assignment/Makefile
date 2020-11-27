CC=g++
CFLAGS=-c -Wall -O2 -std=c++11
LFLAGS=
PROGS= complex_postfix student_hash
OBJS=  complex_postfix.o student_hash.o

# executable targets
all: complex_postfix student_hash

complex_postfix: complex_postfix.o
	$(CC) complex_postfix.o complex_postfix $(LFLAGS)

student_hash: student_hash.o 
	$(CC) student_hash.o student_hash $(LFLAGS)

# object targets
complex_postfix.o: complex_postfix.cpp
	$(CC) complex_postfix.cpp complex_postfix.o $(CFLAGS)

student_hash.o: student_hash.cpp 
	$(CC) student_hash.cpp student_hash.o $(CFLAGS)

clean:
	@rm $(OBJS) $(PROGS)
