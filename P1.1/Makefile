CC=gcc
CFLAGS= -Wall -g -pedantic
EJS = ejemplo1 ejemplo3 ejemplo4 ejemplo2 ejemplo6 ejemplo5
ASM = ej1 ej2 ej3 ej4 ej6 ej5
NASM = nasm -g -o
NFLAGS= -f elf32

.PHONY: all #Genera los archivos de ejecución de los programas en C
all: $(EJS)

generacion.o: generacion.c generacion.h
	$(CC) $(CFLAGS) -c generacion.c

ejemplo1: ejemplo1.o generacion.o
	$(CC) $(CFLAGS) -o ejemplo1 ejemplo1.o generacion.o

ejemplo1.o: ejemplo1.c generacion.h
	$(CC) $(CFLAGS) -c ejemplo1.c

ejemplo2: ejemplo2.o generacion.o
	$(CC) $(CFLAGS) -o ejemplo2 ejemplo2.o generacion.o

ejemplo2.o: ejemplo2.c generacion.h
	$(CC) $(CFLAGS) -c ejemplo2.c

ejemplo3: ejemplo3.o generacion.o
	$(CC) $(CFLAGS) -o ejemplo3 ejemplo3.o generacion.o

ejemplo3.o: ejemplo3.c generacion.h
	$(CC) $(CFLAGS) -c ejemplo3.c

ejemplo4: ejemplo4.o generacion.o
	$(CC) $(CFLAGS) -o ejemplo4 ejemplo4.o generacion.o

ejemplo4.o: ejemplo4.c generacion.h
	$(CC) $(CFLAGS) -c ejemplo4.c

ejemplo5: ejemplo5.o generacion.o
	$(CC) $(CFLAGS) -o ejemplo5 ejemplo5.o generacion.o

ejemplo5.o: ejemplo5.c generacion.h
	$(CC) $(CFLAGS) -c ejemplo5.c

ejemplo6: ejemplo6.o generacion.o
	$(CC) $(CFLAGS) -o ejemplo6 ejemplo6.o generacion.o

ejemplo6.o: ejemplo6.c generacion.h
	$(CC) $(CFLAGS) -c ejemplo6.c

.PHONY: nasm #Ejecuta los programas en C y crea los ejecutables en ensamblador
nasm: $(ASM)

ej1.asm: ejemplo1
	./ejemplo1 ej1.asm

ej1.o: ej1.asm
	$(NASM) ej1.o $(NFLAGS) ej1.asm

ej1: ej1.o alfalib.o
	$(CC) -m32 -o ej1 ej1.o alfalib.o

ej2.asm: ejemplo2
	./ejemplo2 ej2.asm

ej2.o: ej2.asm
	$(NASM) ej2.o $(NFLAGS) ej2.asm

ej2: ej2.o alfalib.o
	$(CC) -m32 -o ej2 ej2.o alfalib.o

ej3.asm: ejemplo3
	./ejemplo3 ej3.asm

ej3.o: ej3.asm
	$(NASM) ej3.o $(NFLAGS) ej3.asm

ej3: ej3.o alfalib.o
	$(CC) -m32 -o ej3 ej3.o alfalib.o

ej4.asm: ejemplo4
	./ejemplo4 ej4.asm

ej4.o: ej4.asm
	$(NASM) ej4.o $(NFLAGS) ej4.asm

ej4: ej4.o alfalib.o
	$(CC) -m32 -o ej4 ej4.o alfalib.o

ej5.asm: ejemplo5
	./ejemplo5 ej5.asm

ej5.o: ej5.asm
	$(NASM) ej5.o $(NFLAGS) ej5.asm

ej5: ej5.o alfalib.o
	$(CC) -m32 -o ej5 ej5.o alfalib.o

ej6.asm: ejemplo6
	./ejemplo6 ej6.asm

ej6.o: ej6.asm
	$(NASM) ej6.o $(NFLAGS) ej6.asm

ej6: ej6.o alfalib.o
	$(CC) -m32 -o ej6 ej6.o alfalib.o

.PHONY: clean #Elimina los ejecutables, los .asm y los .o
clean:
	rm -rf ej*.o generacion.o $(EJS) $(ASM) *.asm

.PHONY: cleano #Solo elimina los .o
cleano:
	rm -rf ej*.o
