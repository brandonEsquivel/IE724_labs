#//  	Ejecute - make all - PARA REALIZAR COMPILACION EJECUCION Y LIMPIEZA
#// 	Ejecute - make COMPILAR - para realizar la compilacion individual
#//	Ejecute - make run - para ejecutar el archivo compilado.
#//	Ejecute make clean para realizar la limpieza de archivos

TARGET = main.exe

CCX = g++
CXXFLAGS 		:= -g -DTEST --debug -I $(INCLUDES) -Wall -pedantic
LINKER = g++
SRCDIR = src
OBJDIR = build
BINDIR = bin
INCDIR = include

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.h)
rm = rm -rf


run:
	./bin/main.exe

COMPILAR:
	@$(CCX) ./$(SRCDIR)/*.cpp -o ./$(BINDIR)/$(TARGET)
	@echo "Compiling done"

clean:
	@$(rm) $(OBJECTS)
	@$(rm) $(OBJDIR)/*.o
	@$(rm) $(BINDIR)/$(TARGET)

all:	COMPILAR run clean

.PHONY: all clean
