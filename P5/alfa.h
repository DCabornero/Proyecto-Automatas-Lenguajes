#ifndef _ALFA_H
#define _ALFA_H

#include <stdio.h>
#include "tablaSimbolos.h"
#include "generacion.h"

#define MAX_LONG_ID 100
#define MAX_VECTOR 64
#define ES_VARIABLE 1
#define ES_INMEDIATO 0
#define GLOBAL 0
#define LOCAL 1

typedef struct{
  char lexema[MAX_LONG_ID+1];
  int tipo;
  int valor_entero;
  int es_direccion;
  int etiqueta;
}tipo_atributos;

#endif
