CC=gcc
CFLAGS= -Wall -g -pedantic
EJS = prueba_tabla
EJSO = tablaHash.o prueba_tabla.o

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(EJS)

tablaHash.o: tablaHash.c tablaHash.h
	$(CC) $(CFLAGS) -c tablaHash.c

prueba_tabla.o: prueba_tabla.c
	$(CC) $(CFLAGS) -c prueba_tabla.c

prueba_tabla: tablaHash.o prueba_tabla.o
	$(CC) $(CFLAGS) -o prueba_tabla $(EJSO)

.PHONY: clean #Elimina los ejecutables, los txt de misalida, los .o y tablaHash.c
clean:
	rm -rf *.o $(EJS)
