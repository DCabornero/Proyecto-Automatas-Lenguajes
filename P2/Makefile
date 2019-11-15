CC=gcc
CFLAGS= -Wall -g -pedantic
EJS = pruebaMorfo

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(EJS)

lex.yy.o: lex.yy.c tokens.h
	$(CC) $(CFLAGS) -c lex.yy.c

lex.yy.c: alfa.l
	flex alfa.l

pruebaMorfo.o: pruebaMorfo.c tokens.h
	$(CC) $(CFLAGS) -c pruebaMorfo.c

pruebaMorfo: lex.yy.o pruebaMorfo.o
	$(CC) $(CFLAGS) -o pruebaMorfo lex.yy.o pruebaMorfo.o

.PHONY: clean #Elimina los ejecutables, los .asm y los .o
clean:
	rm -rf *.o lex.yy.c $(EJS)
