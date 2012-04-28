#!/usr/bin/make

########################################################################

# *** Fill out this information *** 

#  Project Name
PROJECT = button_read_cpp
#  List of the objects files to be compiled/assembled
OBJECTS = main.o

# Selected compiler/architecture
ARCH = gcc/mbed
# Programming language for this project (C for C, CPP for C++)
LANGUAGE = CPP

# Path to the compiler and library
PATH := $(PATH):/home/users/marga/facu/6600/download/gcc-arm-none-eabi-4_6-2012q1/bin
#PATH := $(PATH):/home/marga/facu/tesis/tesisarm/gcc-arm-none-eabi-4_6-2012q1/bin
#PATH := $(PATH):/home/marga/facu/tesis/tesisarm/arm-2011.09/bin
LIB_BASE := ../../src

# Compiling options
DEBUG = -g
OPTIMIZATION = 0
CFLAGS = -Wall

########################################################################

# Include libmanyuc's Makefile to take care of the rest
include $(LIB_BASE)/Makefile

