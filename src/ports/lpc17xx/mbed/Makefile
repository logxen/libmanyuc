#!/usr/bin/make

#  List of the objects files to be compiled/assembled
PORT_OBJECTS = startup_LPC17xx.o port.o io.o serial.o syscalls.o adc.o pwm.o timers.o
PORT_OBJECTS := $(addprefix $(ARCH_DIR)/, $(PORT_OBJECTS))
# Unused hack
#INC_PORT_OBJS = $(addprefix $(ARCH_DIR)/, $(PORT_OBJECTS))
LSCRIPT=$(ARCH_DIR)/LPC17xx.ld

DEBUG ?= -g
OPTIMIZATION ?= 0
#LISTING = -ahls

#  Compiler Options
CFLAGS := $(CFLAGS) -fno-common -mcpu=cortex-m3 -mthumb -I./ -I$(ARCH_DIR) $(INCLUDES) -O$(OPTIMIZATION) $(DEBUG) 
#CFLAGS += -Wcast-align -Wcast-qual -Wimplicit -Wpointer-arith -Wswitch
#CFLAGS += -Wredundant-decls -Wreturn-type -Wshadow -Wunused
LDFLAGS := $(LDFLAGS) -mcpu=cortex-m3 -mthumb -O$(OPTIMIZATION) -nostartfiles -Wl,-Map=$(PROJECT).map -T$(LSCRIPT) 
ASFLAGS = $(LISTING) -mcpu=cortex-m3

CPPFLAGS = $(CFLAGS)
CPPFLAGS += -fno-rtti -fno-exceptions

#  Compiler/Assembler/Linker Paths
CC = arm-none-eabi-gcc
CXX = arm-none-eabi-g++
AS = arm-none-eabi-as
LD = arm-none-eabi-ld
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
REMOVE = rm -f

