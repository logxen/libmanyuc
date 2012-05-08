#!/usr/bin/make

########################################################################
# Internal info

# Selected compiler/architecture
ARCH = test
# Programming language for this project (C for C, CPP for C++)
LANGUAGE = CPP

# Path to the compiler and library
LIB_BASE := ../src

# Compiling options
DEBUG = -g
OPTIMIZATION = 0

# Include the appropriate Makefile
ARCH_DIR = $(LIB_BASE)/ports/$(ARCH)
include $(ARCH_DIR)/Makefile

########################################################################
# CppUTest info

#Set this to @ to keep the makefile quiet
SILENCE = @

COMPONENT_NAME = Libmanyuc
CPPUTEST_HOME = CppUTest

CPPUTEST_USE_EXTENSIONS = N
CPP_PLATFORM = Gcc

SRC_DIRS = \
	$(LIB_BASE) \
	$(LIB_BASE)/cpp \
	$(ARCH_DIR)

TEST_SRC_DIRS = \
	. \
	IOTests \

INCLUDE_DIRS =\
  $(LIB_BASE)/include \
  $(LIB_BASE)/include/cpp \
  $(ARCH_DIR) \
  $(CPPUTEST_HOME)/include \

include $(CPPUTEST_HOME)/build/MakefileWorker.mk
########################################################################

CppUTest/lib/libCppUTest.a:
	make -C CppUTest

dist-clean: clean
	make -C CppUTest clean
	
.PHONY: dist-clean
