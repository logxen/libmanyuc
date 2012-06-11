#!/usr/bin/make

#  List of the objects files to be compiled/assembled
PORT_OBJECTS = io.o serial.o syscalls.o adc.o pwm.o timers.o i2c.o
PORT_OBJECTS := $(addprefix $(ARCH_COMMON_DIR)/, $(PORT_OBJECTS))

#LSCRIPT=$(ARCH_COMMON_DIR)/your.ld

DEBUG ?= -g
OPTIMIZATION ?= 0

#  Compiler Options - Add whatever's needed
CFLAGS := $(CFLAGS) -I./ -I$(ARCH_DIR) -I$(ARCH_COMMON_DIR) $(INCLUDES) -O$(OPTIMIZATION) $(DEBUG) 
LDFLAGS := $(LDFLAGS) -O$(OPTIMIZATION) -nostartfiles -Wl,-Map=$(PROJECT).map -T$(LSCRIPT) 

CPPFLAGS = $(CFLAGS)

#  Compiler/Assembler/Linker Paths
CC = 
CXX =
AS =
LD =
OBJCOPY = 
SIZE = 
REMOVE = 

