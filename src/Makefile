######################################################################
#  Project Makefile - Step Motor library
######################################################################

ARCHIVE		= StepMotor
SRCFILES	= StepMotor.cpp

# Dependencies directory (Header Files)
INCLUDES	+= -I$(TOP_DIR)/src	#StepMotor.h 
INCLUDES	+= -I$(TOP_DIR)/avr-arduino-core/cores
INCLUDES	+= -I$(TOP_DIR)/avr-arduino-core/variants/standard

all: lib clean


# DEPS		= 	# Any additional dependencies for your build
# CLOBBER	+= 	# Any additional files to be removed with "make clobber"

include ../Makefile.incl

######################################################################
#  NOTES:
#	1. remove any modules you don't need from SRCFILES
#	2. "make clean" will remove *.o etc., but leaves *.elf, *.bin
#	3. "make clobber" will "clean" and remove *.elf, *.bin etc.
######################################################################
