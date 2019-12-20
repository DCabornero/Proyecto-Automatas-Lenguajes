CC=gcc
CFLAGS= -Wall -g -pedantic
EJSO = tablaHash.o tablaSimbolos.o
TODO = tablaHash.o tablaSimbolos.o alfa programa1

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(TODO)

generacion.o: generacion.c
	$(CC) $(CFLAGS) -c -o generacion.o generacion.c

tablaHash.o: tablaHash.c
	$(CC) $(CFLAGS) -c -o tablaHash.o tablaHash.c

tablaSimbolos.o: tablaSimbolos.c
	$(CC) $(CFLAGS) -c -o tablaSimbolos.o tablaSimbolos.c

lex.yy.o: lex.yy.c y.tab.h
	$(CC) $(CFLAGS) -c lex.yy.c

y.tab.o: y.tab.c y.tab.h
	$(CC) $(CFLAGS) -c y.tab.c

lex.yy.c: alfa.l
	flex alfa.l

y.tab.c y.tab.h: alfa.y
	bison -d -y -v alfa.y

alfa.o: alfa.c
	$(CC) $(CFLAGS) -c alfa.c

alfa: lex.yy.o y.tab.o alfa.o generacion.o tablaSimbolos.o
	$(CC) $(CFLAGS) -o alfa lex.yy.o y.tab.o alfa.o generacion.o tablaSimbolos.o tablaHash.o

#NASM

programa1.asm: alfa
	./alfa programa1.alfa programa1.asm

programa1.o: programa1.asm
	nasm -felf32 programa1.asm

programa1: programa1.o
	gcc -m32 -o programa1 programa1.o alfalib.o

.PHONY: clean #Elimina los ejecutables, los txt de misalida, los .o y tablaHash.c
clean:
	rm -rf $(EJSO) lex.yy.c lex.yy.o alfa.o y.output y.tab.h y.tab.o y.tab.c generacion.o alfa programa1 programa1.o programa1.asm
