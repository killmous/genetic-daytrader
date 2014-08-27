BUILDDIR    = ./bin/
INCLUDEDIR  = ./include/
SOURCEDIR   = ./genetic-src/

DEFINES     =

SDIRS       = $(wildcard $(SOURCEDIR)*/)
VPATH       = $(SOURCEDIR):$(SDIRS):$(foreach dir, $(SDIRS), $(wildcard $(dir)*/))

IFILES      = $(shell find $(SOURCEDIR) -name '*.cpp')
IFILES     += $(shell find $(SOURCEDIR) -name '*.c')

OFILES      = $(subst $(SOURCEDIR),  $(BUILDDIR), $(addsuffix .o, $(notdir $(shell find $(SOURCEDIR)  -name '*.cpp'))))
OFILES     += $(subst $(SOURCEDIR),  $(BUILDDIR), $(addsuffix .o, $(notdir $(shell find $(SOURCEDIR)  -name '*.c'))))

CXX         = g++
CC          = gcc
CXXFLAGS    = -g -c -w -O3 -std=c++11
CCFLAGS     = -g -c -w -O3
LINKFLAGS   = -pthread -ldl


TARGET = ga

all: $(TARGET)

$(TARGET): $(foreach file, $(OFILES), $(BUILDDIR)$(file))
	$(CXX) $^ $(LINKFLAGS) -o $@

$(BUILDDIR)%.cpp.o: %.cpp
	$(CXX) $(foreach def, $(DEFINES), -D $(def)) $(CXXFLAGS) $< -o $@

$(BUILDDIR)%.c.o: %.c
	$(CC) $(foreach def, $(DEFINES), -D $(def)) $(CCFLAGS) $< -o $@


.PHONY: clean
clean:
	rm $(BUILDDIR)*
	rm $(TARGET)
