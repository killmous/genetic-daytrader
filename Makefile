CC := g++
CFLAGS := -std=c++11
SRCDIR := src/
BINDIR := bin/
EXEC := ga

all:
	g++ $(CFLAGS) -o $(BINDIR)$(EXEC) $(SRCDIR)ga.cpp $(SRCDIR)main.cpp

clean:
	rm $(BINDIR)*