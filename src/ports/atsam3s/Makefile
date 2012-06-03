#!/usr/bin/make

#  List of the objects files to be compiled/assembled
PORT_OBJECTS  = board_lowlevel.o timers.o board_cstartup_gnu.o ints.o
PORT_OBJECTS += syscalls.o io.o adc.o
PORT_OBJECTS := $(addprefix $(ARCH_COMMON_DIR)/, $(PORT_OBJECTS))
LSCRIPT=$(ARCH_COMMON_DIR)/flash.ld

DEBUG ?= -g
OPTIMIZATION ?= 0

#  Compiler Options
CFLAGS += -Wall -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int
CFLAGS += -Werror-implicit-function-declaration -Wmain -Wparentheses
CFLAGS += -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs -Wunused
CFLAGS += -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef
CFLAGS += -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings
CFLAGS += -Wsign-compare -Waggregate-return
CFLAGS += -Wmissing-prototypes -Wmissing-declarations
CFLAGS += -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations
CFLAGS += -Wpacked -Wnested-externs -Winline -Wlong-long
# -Wredundant-decls -Wstrict-prototypes 
CFLAGS += -Wunreachable-code
CFLAGS += -Wcast-align
CFLAGS += -I./ -I$(ARCH_DIR) -I$(ARCH_COMMON_DIR) $(INCLUDES) -O$(OPTIMIZATION) $(DEBUG) 
CFLAGS += --param max-inline-insns-single=500 -mcpu=cortex-m3 -mthumb
CFLAGS += -mlong-calls -ffunction-sections
ASFLAGS += -mcpu=cortex-m3 -mthumb $(DEBUG) $(OPTIMIZATION) $(INCLUDES) -D__ASSEMBLY__

#LDFLAGS := $(LDFLAGS) -mcpu=cortex-m3 -mthumb -O$(OPTIMIZATION) -nostartfiles -Wl,-Map=$(PROJECT).map -T$(LSCRIPT) 
LDFLAGS := $(LDFLAGS) -mcpu=cortex-m3 -mthumb -O$(OPTIMIZATION) -Wl,-Map=$(PROJECT).map -T$(LSCRIPT) 

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

