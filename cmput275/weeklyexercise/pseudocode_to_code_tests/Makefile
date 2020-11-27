CC = g++
LFLAGS = -static
CFLAGS = -c -Wall -02
OBJS = flipflop.o textmatch.o
PROGRAMs = flipflop textmatch





flipflop: flipflop.o textmatch.o
	$(CC) flipflop.o -o flipflop $(LFLAGS)
textmatch: textmatch.o
	$(CC) textmatch.o -o textmatch $(LFLAGS)
flipflop.o: flipflop.cpp 
	$(CC)flipflop.cpp -o flipflop.o -c -Wall $(CFLAGS)
textmatch.o: textmatch.cpp 
	$(CC) textmatch.cpp -o textmatch.o -c -Wall $(CFLAGS)
clean:
	rm -f $(PROGRAMs)
	rm -f $(OBJS)