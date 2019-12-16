#ifndef ALFA_H
#define ALFA_H

#include <stdio.h>
#include "tablaSimbolos.h"
#include "generacion.h"

#define MAX_LONG_ID 100
#define MAX_VECTOR 64
#define GLOBAL 0
#define LOCAL 1

typedef struct _tipo_atributos tipo_atributos;

struct _tipo_atributos{
  char lexema[MAX_LONG_ID+1];
  int tipo;
  int valor_entero;
  int es_direccion;
  int etiqueta;
};


#endif
