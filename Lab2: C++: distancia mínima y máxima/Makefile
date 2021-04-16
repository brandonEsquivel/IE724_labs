TARGET = branch

CCX = g++
LDFLAGS 		:=
CXXFLAGS 		:= -g -DTEST --debug -I $(INCLUDES) -Wall -pedantic
LINKER = g++
SRCDIR = src
OBJDIR = build
BINDIR = bin
INCDIR = include
DOCDIR = doc

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.h)
rm = rm -rf

## Arguments ###### CHANGE THIS VALUES TO DO DIFERENTS TEST
###############################

# 1. Size of the BTH table. (-s)
# 2. Type of prediction (-bp)	[0, 1, 2, 3] = [bimodal, pshare, gshare, tournament]
# 3. Size of the global prediction record (-gh)
# 4. Size of private history records (-ph)
# teacher's test: -s 3 -bp 0 -gh 4 -ph 3
# gshare -s 4 -bp 2 -gh 3 -ph 3
# pshare: -s 5 -bp 1 -gh 3 -ph 2
# Tournament -s 5 -bp 1 -gh 3 -ph 2
S = 3
BP = 0
GH = 4
PH = 3
# The program is able to be executed as follows:
# gunzip -c branch-trace-gcc.trace.gz | branch -s < # > -bp < # > -gh < # > -ph < # >

#############################################################################################3


run:
	gunzip -c branch-trace-gcc.trace.gz > ./src/branch
	@$(CCX) ./$(SRCDIR)/*.cpp -o ./$(BINDIR)/$(TARGET)
	./bin/branch -s $(S) -bp $(BP) -gh $(GH) -ph $(PH) > ./results/actual_result.txt
	rm ./src/branch

all:

$(BINDIR)/$(TARGET): COMPILAR
	@echo "Linker done"
	./bin/branch


COMPILAR:
	@$(CCX) @$(CXXFLAGS) ./$(SRCDIR)/main.cpp -o ./$(BINDIR)/$(TARGET)
	@echo "Compiling done"

unzip:
	gunzip -c ./src/branch-trace-gcc.trace.gz > ./src/branch
	@echo "Extraccion del trace completada"

doc:
	@doxygen Doxyfile
	@echo "Documentation done"


clean:
	@$(rm) $(DOCDIR)/*
	@$(rm) $(OBJECTS)
	@$(rm) $(OBJDIR)/*.o
	@$(rm) $(BINDIR)/$(TARGET)
	rm ./src/branch

.PHONY: all clean doc
