# This Makefile provides targets for building third_party libraries to $(LIB).

third_party: mk_install_dir gflags glog gtest zmq3-2

mk_install_dir:
	mkdir -p $(THIRD_PARTY_INSTALLED)

gflags:
	cd $(THIRD_PARTY)/gflags-2.0;\
		./configure --prefix=$(THIRD_PARTY_INSTALLED);\
		make check install clean distclean

# Needed by glog
libunwind:
	cd $(THIRD_PARTY)/libunwind-1.1;\
		./configure --prefix=$(THIRD_PARTY_INSTALLED);\
		make install clean distclean

glog: libunwind
	cd $(THIRD_PARTY)/glog-0.3.3;\
		./configure CPPFLAGS=-I$(THIRD_PARTY_INSTALLED)/include --prefix=$(THIRD_PARTY_INSTALLED);\
		make install #clean distclean

zmq3-2:
	cd $(THIRD_PARTY)/zeromq-3.2.3;\
		./configure --prefix=$(THIRD_PARTY_INSTALLED);\
		make install #clean distclean
	cp $(THIRD_PARTY)/zmq.hpp $(THIRD_PARTY_INSTALLED)/include


# gtest does not use autoconf, so the Makefile is lengthy and thus maintained
# separately.
include $(THIRD_PARTY)/gtest.mk

gtest: gtest-build
