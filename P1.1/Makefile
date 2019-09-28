CC=gcc
CFLAGS= -Wall -g -pedantic
EJS = ejemplo1 ejemplo3 ejemplo4 ejemplo2


.PHONY: all
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



.PHONY: clean
clean:
	rm -rf ej*.o generacion.o $(EJS)
