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
/*Asociatividad Previa:
%right TOK_ASIGNACION
%left TOK_OR
%left TOK_AND
%left TOK_IGUAL TOK_DISTINTO
%left TOK_MENOR TOK_MENORIGUAL TOK_MAYOR TOK_MAYORIGUAL
%left TOK_MAS TOK_MENOS
%left TOK_DIVISION TOK_ASTERISCO
%right TOK_NOT
%left TOK_PARENTESISIZQUIERDO TOK_PARENTESISDERECHO
*/

#endif
