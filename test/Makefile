CPPFLAGS	= -I..
CPPFLAGS	+= -DBOOST_TEST_MAIN -DBOOST_TEST_DYN_LINK
CXX_BASE	= -ggdb3 $(CPPFLAGS)
#CXX_BASE	+= -Wall -Wextra -Werror
CXXFLAGS	= $(CXX_BASE) -O0
CXX_OPT		= $(CXX_BASE) -O3 -fomit-frame-pointer
CXX_OPT		+= -DNDEBUG
LIBS		= -lboost_unit_test_framework

TARGETS		= $(patsubst %.cpp, %, $(wildcard *.cpp))

CLEANFILES	:= $(TARGETS)
CLEANFILES	+= $(TARGETS:%=.%.d)
CLEANFILES	+= $(TARGETS:%=%.i)
CLEANFILES	+= $(TARGETS:%=.%.i.d)

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) -MD -MF .$*.d -o $@ $*.cpp $(LIBS)

runtests: $(TARGETS)
	@for target in $(TARGETS); do \
	    echo -n "$$target tests: "; \
	    ./$$target; \
	done

.SUFFIXES: .lst .lst.o .i .hpp

%.lst: %.lst.o
	objdump -rdSC $? > $@

%.lst.o: %.cpp
	$(CXX) $(CXX_OPT) -MD -MF .$*.lst.d -o $@ -c $*.cpp

%.i: %.cpp
	$(CXX) $(CPPFLAGS) -MD -MT $@ -MF .$*.i.d -o $@ -E $*.cpp

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
