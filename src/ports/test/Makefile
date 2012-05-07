#!/usr/bin/make

#  List of the objects files to be compiled/assembled
PORT_OBJECTS = port.o io.o
PORT_OBJECTS := $(addprefix $(ARCH_DIR)/, $(PORT_OBJECTS))

DEBUG ?= -g
OPTIMIZATION ?= 0

#  Compiler Options
CFLAGS := $(CFLAGS) -I./ -I$(ARCH_DIR) $(INCLUDES) -O$(OPTIMIZATION) $(DEBUG) 
LDFLAGS = -O$(OPTIMIZATION) -e init
ASFLAGS = $(LISTING) 

CPPFLAGS = $(CFLAGS)

#  Compiler/Assembler/Linker Paths
CC = gcc
CXX = g++
AS = as
LD = ld
OBJCOPY = objcopy
SIZE = size
REMOVE = rm -f

