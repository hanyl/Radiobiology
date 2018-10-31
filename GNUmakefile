# $Id: GNUmakefile,v 1.2 2006/10/02 16:25:55 vnivanch Exp $
# --------------------------------------------------------------
# GNUmakefile for examples module.  Gabriele Cosmo, 06/04/98.
# --------------------------------------------------------------

name := g4fot
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../../..
endif

ROOTSYS=/Applications/root
ROOTLIBS=`$(ROOTSYS)/bin/root-config --libs`
ROOTCFLAGS=`$(ROOTSYS)/bin/root-config --cflags`
LDLIBS3 += $(ROOTLIBS)

CPPFLAGS += $(ROOTCFLAGS)
CPPFLAGS += -I./Fot
.PHONY: all
all: lib bin

include $(G4INSTALL)/config/binmake.gmk
LDFLAGS += -L./Fot -lfot

ifdef G4ANALYSIS_USE
  # for the aida-config command see the README file
  CPPFLAGS += `aida-config --include`
  LDLIBS  += `aida-config --lib`  

plots:	plotResults.class
	@echo calling JAIDA ...
	java -cp .:$(CLASSPATH) plotResults ppsim.aida

plotResults.class: plotResults.java
	@echo compiling $<
	javac $<
endif
