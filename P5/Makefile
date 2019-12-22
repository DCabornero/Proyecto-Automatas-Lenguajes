CC=gcc
CFLAGS= -Wall -g -pedantic
EJSO = tablaHash.o tablaSimbolos.o alfa.o generacion.o programa1.o programa2.o programa3.o programa4.o programa5.o programa6.o programa7.o programa8.o
ALL = tablaHash.o tablaSimbolos.o alfa programa1 programa2 programa3 programa4 programa5 programa6 programa7 programa8
LEX = lex.yy.c lex.yy.o
YTAB = y.output y.tab.h y.tab.o y.tab.c
ASM = programa1.asm programa2.asm programa3.asm programa4.asm programa5.asm programa6.asm programa7.asm programa8.asm
EXEC = alfa programa1 programa2 programa3 programa4 programa5 programa6 programa7 programa8


.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(ALL)

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

programa2.asm: alfa
	./alfa programa2.alfa programa2.asm

programa2.o: programa2.asm
	nasm -felf32 programa2.asm

programa2: programa2.o
	gcc -m32 -o programa2 programa2.o alfalib.o

programa3.asm: alfa
	./alfa programa3.alfa programa3.asm

programa3.o: programa3.asm
	nasm -felf32 programa3.asm

programa3: programa3.o
	gcc -m32 -o programa3 programa3.o alfalib.o

programa4.asm: alfa
	./alfa programa4.alfa programa4.asm

programa4.o: programa4.asm
	nasm -felf32 programa4.asm

programa4: programa4.o
	gcc -m32 -o programa4 programa4.o alfalib.o

programa5.asm: alfa
	./alfa programa5.alfa programa5.asm

programa5.o: programa5.asm
	nasm -felf32 programa5.asm

programa5: programa5.o
	gcc -m32 -o programa5 programa5.o alfalib.o

programa6.asm: alfa
	./alfa programa6.alfa programa6.asm

programa6.o: programa6.asm
	nasm -felf32 programa6.asm

programa6: programa6.o
	gcc -m32 -o programa6 programa6.o alfalib.o

programa7.asm: alfa
	./alfa programa7.alfa programa7.asm

programa7.o: programa7.asm
	nasm -felf32 programa7.asm

programa7: programa7.o
	gcc -m32 -o programa7 programa7.o alfalib.o

programa8.asm: alfa
	./alfa programa8.alfa programa8.asm

programa8.o: programa8.asm
	nasm -felf32 programa8.asm

programa8: programa8.o
	gcc -m32 -o programa8 programa8.o alfalib.o

.PHONY: clean #Elimina los ejecutables, los txt de misalida, los .o y tablaHash.c
clean:
	rm -rf $(EJSO) $(LEX) $(YTAB) $(ASM) $(EXEC)
