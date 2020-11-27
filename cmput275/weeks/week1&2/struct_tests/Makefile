# Defining variables
CXX = g++
CXXFLAGS = -Wall -g
BINARIES = struct alignment

# Rule format: 
# target: prereq1 prereq2
# 	  commands

all: struct alignment

clean:
	rm -f $(BINARIES) *.o

struct: struct.o
	$(CXX) $(CXXFLAGS) -o struct struct.o

struct.o: struct.cpp
	$(CXX) $(CXXFLAGS) -c struct.cpp

alignment: alignment.o
	$(CXX) $(CXXFLAGS) -o alignment alignment.o

alignment.o: alignment.cpp
	$(CXX) $(CXXFLAGS) -c alignment.cpp
