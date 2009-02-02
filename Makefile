SUBDIRS		:= bench sample test

all:		$(SUBDIRS:%=%/all)
clean:		$(SUBDIRS:%=%/clean)
install:	$(SUBDIRS:%=%/install)

$(SUBDIRS:%=%/all):
	$(MAKE) -$(MAKEFLAGS) -C $(dir $@) all

$(SUBDIRS:%=%/clean):
	$(MAKE) -$(MAKEFLAGS) -C $(dir $@) clean

$(SUBDIRS:%=%/install):
	$(MAKE) -$(MAKEFLAGS) -C $(dir $@) clean

.NOTPARALLEL:
