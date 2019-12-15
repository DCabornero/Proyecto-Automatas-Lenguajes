CC=gcc
CFLAGS= -Wall -g -pedantic
EJSO = tablaHash.o tablaSimbolos.o
TODO = tablaHash.o tablaSimbolos.o alfa

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(TODO)

tablaHash.o: tablaHash.c tablaHash.h
	$(CC) $(CFLAGS) -c tablaHash.c

tablaSimbolos.o: tablaSimbolos.c tablaSimbolos.h
	$(CC) $(CFLAGS) -c tablaSimbolos.c

lex.yy.o: lex.yy.c y.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c

y.tab.o: y.tab.c y.tab.h
	$(CC) $(CFLAGS) -c y.tab.c

lex.yy.c: alfa.l
	flex alfa.l

y.tab.c y.tab.h: alfa.y
	bison -d -y -v alfa.y

alfa.o: alfa.c y.tab.h alfa.h
	$(CC) $(CFLAGS) -c alfa.c

alfa: lex.yy.o y.tab.o alfa.o
	$(CC) $(CFLAGS) -o alfa lex.yy.o y.tab.o alfa.o

.PHONY: clean #Elimina los ejecutables, los txt de misalida, los .o y tablaHash.c
clean:
	rm -rf $(EJSO) lex.yy.c lex.yy.o alfa.o tablaHash.o tablaSimbolos.o y.output y.tab.h y.tab.o
