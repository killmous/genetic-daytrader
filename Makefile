CC := g++
CFLAGS := -std=c++11 -O3
SRCDIR := src/
BINDIR := bin/
EXEC := ga

all:
	$(CC) $(CFLAGS) -o $(BINDIR)$(EXEC) $(SRCDIR)ga.cpp $(SRCDIR)main.cpp

clean:
	rm $(BINDIR)*