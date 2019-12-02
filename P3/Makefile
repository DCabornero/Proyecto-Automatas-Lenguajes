CC=gcc
CFLAGS= -Wall -g -pedantic
EJS = pruebaTabla
EJSO = tablaHash.o pruebaTabla.o

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(EJS)

tablaHash.o: tablaHash.c tablaHash.h
	$(CC) $(CFLAGS) -c tablaHash.c

pruebaTabla.o: pruebaTabla.c
	$(CC) $(CFLAGS) -c pruebaTabla.c

pruebaTabla: tablaHash.o pruebaTabla.o
	$(CC) $(CFLAGS) -o pruebaTabla $(EJSO)

.PHONY: clean #Elimina los ejecutables, los txt de misalida, los .o y tablaHash.c
clean:
	rm -rf *.o $(EJS)
