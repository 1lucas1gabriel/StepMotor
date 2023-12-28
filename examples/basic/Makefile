######################################################################
#  Project - Example StepMotor Basic
######################################################################

BINARY		= basic
SRCFILES	= basic.cpp

# Dependecies Directory (Header Files)
INCLUDES	+= -I$(TOP_DIR)/src	#StepMotor.h
INCLUDES	+= -I$(TOP_DIR)/avr-arduino-core/cores
INCLUDES	+= -I$(TOP_DIR)/avr-arduino-core/variants/standard

# Dependencies Directory (Static Libs Folder)
LDFLAGS		+= -L$(TOP_DIR)/src
LDFLAGS		+= -L$(TOP_DIR)/avr-arduino-core/cores

# Dependencies (Static Lib Files .a)
LDLIBS		+= -lStepMotor
LDLIBS		+= -lcore_atmega328p			#last


all: hex clean

include ../../Makefile.incl

# End
