CC=gcc
CFLAGS= -Wall -g -pedantic
EJSO = tablaHash.o tablaSimbolos.o

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: tablaHash.o tablaSimbolos.o

tablaHash.o: tablaHash.c tablaHash.h
	$(CC) $(CFLAGS) -c tablaHash.c

tablaSimbolos.o: tablaSimbolos.c tablaSimbolos.h
	$(CC) $(CFLAGS) -c tablaSimbolos.c

.PHONY: clean #Elimina los ejecutables, los txt de misalida, los .o y tablaHash.c
clean:
	rm -rf *.o $(EJS)
