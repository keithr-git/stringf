CXX_BASE	= $(CPPFLAGS) -g -I..
CXX_BASE	+= -Wall -Wextra -Werror

CXX_OPT		:= $(CXX_BASE) -O3 -fomit-frame-pointer
CXX_OPT 	+= -DNDEBUG

CXXFLAGS	:= $(CXX_BASE) -O0

TARGETS		= $(patsubst %.cpp, %, $(wildcard *.cpp))

CLEANFILES	:= $(TARGETS)
CLEANFILES	+= $(TARGETS:%=.%.d)
CLEANFILES	+= $(TARGETS:%=%.i)
CLEANFILES	+= $(TARGETS:%=.%.i.d)
CLEANFILES	+= $(TARGETS:%=%.lst)
CLEANFILES	+= $(TARGETS:%=%.lst.o)
CLEANFILES	+= $(TARGETS:%=.%.lst.d)

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -MD -MF .$*.d -o $@ $*.cpp $(LIBS)

.SUFFIXES: .lst .lst.o .i

%.lst: %.lst.o __ALWAYS
	objdump -rdSC $*.lst.o > $@

%.lst.o: %.cpp __ALWAYS
	$(CXX) $(CXX_OPT) -MD -MF .$*.lst.d -o $@ -c $*.cpp

%.i: %.cpp __ALWAYS
	$(CXX) $(CXXFLAGS) -o - -E $*.cpp | cb++ > $@

DEPFILES	= $(wildcard .*.d)

.PHONY: __ALWAYS

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
