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
LINKER      = $(CXX)
ARCH        = 64

CXXFLAGS    = -c -g -w -O3 -m$(ARCH) -std=c++0x
CCFLAGS     = -c -g -w -O3 -m$(ARCH)
LINKFLAGS   = -pthread -ldl -m$(ARCH)


TARGET = ga

all: $(TARGET)

$(TARGET): $(foreach file, $(OFILES), $(BUILDDIR)$(file))
	$(LINKER) $^ $(LINKFLAGS) -o $@

$(BUILDDIR)%.cpp.o: %.cpp
	$(CXX) $(foreach def, $(DEFINES), -D $(def)) $(CXXFLAGS) $< -o $@

$(BUILDDIR)%.c.o: %.c
	$(CC) $(foreach def, $(DEFINES), -D $(def)) $(CCFLAGS) $< -o $@


.PHONY: clean
clean:
	rm $(BUILDDIR)*
	rm $(TARGET)
