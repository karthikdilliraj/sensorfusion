# ------------------------------------------------
# Generic Makefile
#
# Author: nhathieugc@gmail.com
# Date  : 2019-11-10
#
# Changelog :
# 2019-11-10: Inital Draft
# 2019-11-11: Makefile with GSL library
#
# ------------------------------------------------

# project name (generate executable with this name)
TARGET   = sensorfusion

# change these to proper directories where each file should be
SRCDIR     	 = src
OBJDIR    	 = obj
BINDIR    	 = bin
INCDIR	  	 = include
GSLLIBDIR    = lib/gsl/lib
GSLINCDIR 	 = lib/gsl/include

CC       = gcc
# compiling flags here
CFLAGS   = -std=c99 -Wall

LFLAGS   = -L$(GSLLIBDIR) -lgsl -lgslcblas -lm

INC      := -I$(INCDIR) -I$(GSLINCDIR)
SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@$(CC) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS) $(BINDIR)/$(TARGET)
	@echo "Cleanup complete!"
