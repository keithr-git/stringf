CXXFLAGS	= -ggdb3 -I..
CXXFLAGS	+= $(CXX_BASE) -O3 -fomit-frame-pointer
CXXFLAGS	+= -DNDEBUG

TARGETS		= $(patsubst %.cpp, %, $(wildcard *.cpp))

CLEANFILES	:= $(TARGETS)
CLEANFILES	+= $(TARGETS:%=.%.d)
CLEANFILES	+= $(TARGETS:%=%.i)
CLEANFILES	+= $(TARGETS:%=%.lst)
CLEANFILES	+= $(TARGETS:%=%.lst.o)
CLEANFILES	+= $(TARGETS:%=.%.lst.d)

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -MD -MF .$*.d -o $@ $*.cpp $(LIBS)

.SUFFIXES: .lst .lst.o

%.lst: %.lst.o
	objdump -rdSC $? > $@

%.lst.o: %.cpp
	$(CXX) $(CXX_OPT) -MD -MF .$*.lst.d -o $@ -c $*.cpp

DEPFILES	= $(wildcard .*.d)

ifneq ($(DEPFILES),)
include $(DEPFILES)
endif

CLEANFILES	:= $(wildcard $(CLEANFILES))

clean:
ifdef CLEANFILES
	$(RM) -f $(CLEANFILES)
endif

#
# The heavy template usage makes g++ use LOTS of memory.
# Parallel execution brings the system to its knees.
#
.NOTPARALLEL:
