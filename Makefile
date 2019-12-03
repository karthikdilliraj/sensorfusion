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
SRCTESTDIR	 = test
OBJDIR    	 = obj
BINDIR    	 = bin
INCDIR	  	 = include
INCTESTDIR	 = test/include
GSLLIBDIR    = lib/gsl/lib
GSLINCDIR 	 = lib/gsl/include

CC       = gcc
# compiling flags here
CFLAGS   = -Wall

LFLAGS   = -L$(GSLLIBDIR) -lgsl -lgslcblas -lm

INC      := -I$(INCDIR) -I$(GSLINCDIR) -I$(INCTESTDIR)
SOURCES  := $(wildcard $(SRCDIR)/*.c)
TSOURCES := $(wildcard $(SRCTESTDIR)/*.c)
OBJECTS1 := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTS2 := $(TSOURCES:$(SRCTESTDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS1) $(OBJECTS2)
	@mkdir -p $(BINDIR)
	@$(CC) $(OBJECTS1) $(OBJECTS2) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS1): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(OBJECTS2): $(OBJDIR)/%.o : $(SRCTESTDIR)/%.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS1) $(OBJECTS2) $(BINDIR)/$(TARGET)
	@echo "Cleanup complete!"
