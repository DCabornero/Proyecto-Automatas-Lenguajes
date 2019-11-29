CC=gcc
CFLAGS= -Wall -g -pedantic
EJS = pruebaSintactico

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(EJS)

lex.yy.o: lex.yy.c y.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c

y.tab.o: y.tab.c y.tab.h
	$(CC) $(CFLAGS) -c y.tab.c

lex.yy.c: alfa.l
	flex alfa.l

y.tab.c y.tab.h: alfa.y
	bison -d -y -v alfa.y

pruebaSintactico.o: pruebaSintactico.c y.tab.h
	$(CC) $(CFLAGS) -c pruebaSintactico.c

pruebaSintactico: lex.yy.o y.tab.o pruebaSintactico.o
	$(CC) $(CFLAGS) -o pruebaSintactico lex.yy.o y.tab.o pruebaSintactico.o

.PHONY: clean #Elimina los ejecutables, los txt de misalida, los .o y lex.yy.c
clean:
	rm -rf *.o lex.yy.c $(EJS) misalida*.txt y.output y.tab.c y.tab.h
