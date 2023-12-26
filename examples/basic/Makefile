######################################################################
#  Project - Example StepMotor Basic
######################################################################

BINARY		= basic
SRCFILES	= basic.cpp

# Dependecies Directory (Header Files)
INCLUDES	+= -I$(TOP_DIR)/StepMotor/src	#StepMotor.h

# Dependencies Directory (Static Libs Folder)
LDFLAGS		+= -L$(TOP_DIR)/StepMotor/src
LDFLAGS		+= -L$(ARDUINO_CORE_DIR)

# Dependencies (Static Lib Files .a)
LDLIBS		+= -lStepMotor
LDLIBS		+= -lcore_atmega328p			#last


all: hex clean

include ../../../Makefile.incl

# End
