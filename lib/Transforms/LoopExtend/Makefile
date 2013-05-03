#Makefile for hello pass

# Path to top level of LLVM hierarchy
LEVEL = ../../..

# Name of the library to build
LIBRARYNAME = LoopExtended

# Make the shared library become a loadable module so the tools can
# dlopen/dlsym on the resulting library.
LOADABLE_MODULE = 1

CFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cflags)
CXXFLAGS+=$(COMMON_FLAGS) $(shell $(LLVM_CONFIG) --cxxflags)

ifeq ($(shell uname -m),x86_64)
CFLAGS+=-fPIC
CXXFLAGS+=-fPIC
endif
#LINK_COMPONENTS := all
# Include the makefile implementation stuff
include $(LEVEL)/Makefile.common
