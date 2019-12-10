#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H
#include <stdio.h>
#include <stdlib.h>
#include "tablaHash.h"
#define MAX_TABLA_SIMBOLOS 65536

typedef enum { OK, ERROR } STATUS;

STATUS declarar(char* id, SIMBOLO* desc_id);
SIMBOLO* usoGlobal(char* id);
SIMBOLO* usoLocal(char* id);
STATUS declararFuncion(char* id, SIMBOLO* desc_id);
STATUS cerrarFuncion();
void eliminar();

#endif
