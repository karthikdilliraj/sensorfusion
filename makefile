# ------------------------------------------------
# Generic Makefile
#
# Author: nhathieugc@gmail.com
# Date  : 2019-11-10
#
# Changelog :
#
# ------------------------------------------------

# project name (generate executable with this name)
TARGET   = sensorfusion

CC       = gcc
# compiling flags here
CFLAGS   = -std=c99 -Wall

# change these to proper directories where each file should be
SRCDIR   = src
OBJDIR   = obj
BINDIR   = bin
INCDIR	 = include

INC      := -I$(INCDIR)
SOURCES  := $(wildcard $(SRCDIR)/*.c)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(BINDIR)
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
	@$(rm) $(OBJECTS) $(BINDIR)/$(TARGET)
	@echo "Cleanup complete!"